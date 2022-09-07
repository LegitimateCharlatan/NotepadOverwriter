
### Notepad Overwriter

It fetches existing text from active notepad and overwrites it with what was supplied in command line arguments

### Build

```
msbuild NotepadOverwriter.sln /p:Configuration=Release
```

### Winapi used

```
OpenProcess
CreateToolhelp32Snapshot
Process32First
Process32Next
GetClassName
GetWindowThreadProcessId
EnumWindows
EnumChildWindows
SendMessage
CloseHandle
```