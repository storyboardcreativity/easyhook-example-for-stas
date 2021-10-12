#pragma once
#include <Windows.h>

typedef DWORD (__stdcall *WriteFile_PTR)(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);

void FunctionHooksInit();
void FunctionHooksDeInit();