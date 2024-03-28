// 启动.cpp : 定义应用程序的入口点。
//

#include <Windows.h>
#include <iostream>
DWORD WINAPI LoadDllThread(LPVOID lpParam);
bool RegisterCOMComponent(const char* dllPath, bool showWindow = false);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (RegisterCOMComponent("op_x64.dll")) {
        std::cout << "COM component registered successfully." << std::endl;
    }
    else {
        std::cerr << "Failed to register COM component." << std::endl;
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
    //OutputDebugStringA("MRZHUGE_调用成功\n");
    // 等待线程完成
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    return 0;

    return 0;
}

//静默注册com
bool RegisterCOMComponent(const char* dllPath, bool showWindow) {
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    if (!showWindow) {
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.wShowWindow = SW_HIDE; // 隐藏窗口
    }

    ZeroMemory(&pi, sizeof(pi));

    std::string command = "regsvr32 /s "; // /s 参数使 regsvr32 以无声模式运行
    command += dllPath; // 添加DLL路径

    // 创建进程以执行命令
    if (!CreateProcessA(
        NULL,
        const_cast<LPSTR>(command.c_str()), // 因为CreateProcessA可能会更改字符串
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi)) {
        std::cerr << "CreateProcess failed (" << GetLastError() << ")." << std::endl;
        return false;
    }

    // 等待注册过程完成
    WaitForSingleObject(pi.hProcess, INFINITE);

    // 关闭进程和线程句柄
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return true;
}

DWORD WINAPI LoadDllThread(LPVOID lpParam) {
    const char* dllPath = static_cast<const char*>(lpParam);
    HMODULE hModule = LoadLibraryA(dllPath);
    if (hModule == NULL) {
        // 处理错误
        OutputDebugStringA("MRZHUGE_LoadLibrary failed:\n ");
    }
    else {
        typedef DWORD(*ShowDialog)();
        ShowDialog start = (ShowDialog)GetProcAddress(hModule, "ShowDialog");
        DWORD r = start();
        OutputDebugStringA("MRZHUGE_调用成功\n");
    }
    return 0;
}