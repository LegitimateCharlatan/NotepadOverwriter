#include "utils.h"
#include <tlhelp32.h>
#include <Winuser.h>
#include <Richedit.h>

struct Container {
    DWORD targetProcessId;
    HWND childWindowId;
    HWND windowId;
};

DWORD getProcessIdByName(LPCWSTR processName)
{
    PROCESSENTRY32 entry{};
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (!Process32First(snapshot, &entry))
    {
        CloseHandle(snapshot);
        return 0;
    }

    while (Process32Next(snapshot, &entry))
    {
        if (lstrcmp(entry.szExeFile, processName) == 0)
        {
            return entry.th32ProcessID;
        }
    }

    CloseHandle(snapshot);

    return 0;
}

BOOL CALLBACK EnumChildWindowsCallback(HWND hWnd, LPARAM lParam)
{
    Container* container = (Container*)lParam;
    WCHAR className[256];
    GetClassName(hWnd, className, sizeof(className));

    if (lstrcmp(className, L"RichEditD2DPT") == 0)
    {
        container->windowId = hWnd;
        return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    Container* container = (Container*)lParam;
    DWORD processId = 0;
    GetWindowThreadProcessId(hwnd, &processId);

    if (processId == container->targetProcessId)
    {
        container->windowId = hwnd;
        return FALSE;
    }

    return TRUE;
}

HWND getFirstWindow(DWORD processId)
{
    Container* container = new Container();
    container->windowId = NULL;
    container->targetProcessId = processId;
    EnumWindows(EnumWindowsProc, (LPARAM)container);
    return container->windowId;
}

HWND getEditTextControl(HWND hwndParent)
{
    Container* container = new Container();
    container->windowId = NULL;
    EnumChildWindows(hwndParent, EnumChildWindowsCallback, (LPARAM)container);
    return container->windowId;
}

LPCWSTR getText(HWND control)
{
    LRESULT length = SendMessage(control, WM_GETTEXTLENGTH, 0, 0);
    wchar_t* buffer = new wchar_t[length + 1];
    SendMessage(control, WM_GETTEXT, (WPARAM)length, (LPARAM)buffer);
    return buffer;
}


void updateText(HWND control, LPCWSTR text)
{
    SendMessage(control, WM_SETTEXT, 0, (LPARAM)text);
}
