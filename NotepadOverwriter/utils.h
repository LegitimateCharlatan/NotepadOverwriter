#pragma once
#include <Windows.h>

DWORD getProcessIdByName(LPCWSTR processName);
BOOL CALLBACK EnumChildWindowsCallback(HWND hWnd, LPARAM lParam);
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
HWND getFirstWindow(DWORD processId);
HWND getEditTextControl(HWND hwndParent);
LPCWSTR getText(HWND control);
void updateText(HWND control, LPCWSTR text);