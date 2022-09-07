#include <iostream>
#include <Shlwapi.h>
#include <psapi.h>
#include <tlhelp32.h>
#include "utils.h"

int wmain(int argc, wchar_t** argv)
{
    if (argc < 1)
    {
        puts("Provide text to write in notepad process");
    }

    LPCWSTR text_to_write = argv[1];
    DWORD processId = getProcessIdByName(L"Notepad.exe");

    if (!processId) {
        puts("Notepad process not found");
        return EXIT_SUCCESS;
    }

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    
    if (hProcess == 0) {
        puts("Could not open process");
        return EXIT_SUCCESS;
    }
    
    HWND firstWindow = getFirstWindow(processId);
    HWND control = getEditTextControl(firstWindow);
    
    LPCWSTR text = getText(control);
    printf("Current text: %ls\n", text);
    updateText(control, text_to_write);

    delete text;
    CloseHandle(hProcess);
    return EXIT_SUCCESS;
}