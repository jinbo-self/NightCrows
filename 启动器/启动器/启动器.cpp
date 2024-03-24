#include <Windows.h>
#include <iostream>

// 函数声明
DWORD WINAPI LoadDllThread(LPVOID lpParam);
int main() {
    // 目标进程的窗口标题
    // 查找窗口
    HWND hWndConsole = GetConsoleWindow();
    if (hWndConsole != NULL) {
        // 隐藏控制台窗口
        ShowWindow(hWndConsole, SW_MINIMIZE);
    }
    HWND hwnd = FindWindow(L"UnrealWindow", L"NIGHT CROWS(1)  ");
    if (hwnd == NULL) {
        OutputDebugStringA("Window not found!\n");
        return 1;
    }
    if (!MoveWindow(hwnd, 0, 0, 1280, 756, TRUE)) {
        OutputDebugStringA("MRZHUGE_Failed to move window.\n");
        return 1;
    }
    const char* dllPath = "ML.dll";
    DWORD threadId;
    HANDLE hThread = CreateThread(NULL, 0, LoadDllThread, (void*)dllPath, 0, &threadId);
    if (hThread == NULL) {
        // 处理错误
        OutputDebugStringA("MRZHUGE_CreateThread failed\n");
        return 1;
    }
    OutputDebugStringA("MRZHUGE_调用成功\n");
    // 等待线程完成
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    return 0;
}
DWORD WINAPI LoadDllThread(LPVOID lpParam) {
    const char* dllPath = static_cast<const char*>(lpParam);
    HMODULE hModule = LoadLibraryA(dllPath);
    if (hModule == NULL) {
        // 处理错误
        OutputDebugStringA("MRZHUGE_LoadLibrary failed:\n ");
    }
    else {
        typedef DWORD (*ShowDialog)();
        ShowDialog start = (ShowDialog)GetProcAddress(hModule, "ShowDialog");
        DWORD r = start();
        OutputDebugStringA("MRZHUGE_调用成功\n");
    }
    return 0;
}
