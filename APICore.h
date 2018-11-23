#pragma once

/*
*   APICore.h - модуль включает необходимые заголовочные файлы.
*	Автор: Shkolnik Prahramist (c) 2018.
*/

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "Comctl32.lib")

#include <Windows.h>
#include <string>
#include <thread>
#include <algorithm>
#include <d2d1.h>
#include <dwrite.h>
#include <dwmapi.h>
#include <CommCtrl.h>
#include <UIAnimation.h>