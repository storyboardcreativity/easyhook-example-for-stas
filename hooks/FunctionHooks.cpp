#include "FunctionHooks.h"

#include <iostream>
#include <stdio.h>

#include "external_libs/easyhook.h"

HOOK_TRACE_INFO hHook = { nullptr };

DWORD __stdcall WriteFile_wrapper(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
{
	printf("Params: hFile == 0x%llX\n", (uint64_t)hFile);
	printf("Params: lpBuffer == 0x%llX\n", (uint64_t)lpBuffer);
	printf("Params: nNumberOfBytesToWrite == 0x%llX\n", (uint64_t)nNumberOfBytesToWrite);
	printf("Params: lpNumberOfBytesWritten == 0x%llX\n", (uint64_t)lpNumberOfBytesWritten);
	printf("Params: lpOverlapped == 0x%llX\n", (uint64_t)lpOverlapped);

	auto result = WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);

	printf("Finished!\n");
	return result;
}

DWORD __stdcall WriteFileEx_wrapper(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPOVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	printf("Params: hFile == 0x%llX\n", (uint64_t)hFile);
	printf("Params: lpBuffer == 0x%llX\n", (uint64_t)lpBuffer);
	printf("Params: nNumberOfBytesToWrite == 0x%llX\n", (uint64_t)nNumberOfBytesToWrite);
	printf("Params: lpNumberOfBytesWritten == 0x%llX\n", (uint64_t)lpNumberOfBytesWritten);
	printf("Params: lpOverlapped == 0x%llX\n", (uint64_t)lpOverlapped);

	auto result = WriteFileEx(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);

	printf("Finished!\n");
	return result;
}

void FunctionHooksDeInit()
{
	LhWaitForPendingRemovals();
}

void FunctionHooksInit()
{
	// Install the hook
	NTSTATUS result = LhInstallHook(
		GetProcAddress(GetModuleHandle(TEXT("kernel32")), "WriteFile"),
		WriteFile_wrapper,
		NULL,
		&hHook);

	if (FAILED(result))
		return;

	ULONG ACLEntries[1] = { 0 };
	LhSetExclusiveACL(ACLEntries, 1, &hHook);
}
