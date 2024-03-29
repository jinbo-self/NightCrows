// 启动.cpp : 定义应用程序的入口点。
//

// client_windows.cpp
#include <iostream>
#include <fstream>
#include <winsock2.h>
#include <Ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib") // 链接到Windows Socket库

#define PORT 8080
#define IP "192.168.200.129"
#define PORT 8080
DWORD WINAPI LoadDllThread(LPVOID lpParam);
bool RegisterCOMComponent(const char* dllPath, bool showWindow = false);
void receiveFile(int sock);
void receiveFile(int sock) {
    std::ofstream outFile("ML.dll", std::ios::binary);
    char buffer[1024] = { 0 };

    if (outFile.is_open()) {
        int bytesReceived = 0;
        while ((bytesReceived = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
            outFile.write(buffer, bytesReceived);
            memset(buffer, 0, sizeof(buffer));
        }
        outFile.close();
        std::cout << "File received successfully" << std::endl;
    }
    else {
        std::cout << "Failed to open file for writing" << std::endl;
    }
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    //检查云更：
    //WSADATA wsaData;
    //SOCKET sock = INVALID_SOCKET;
    //struct sockaddr_in serv_addr;

    //// 初始化Winsock
    //int res = WSAStartup(MAKEWORD(2, 2), &wsaData);
    //if (res != 0) {
    //    std::cout << "Winsock init failed with error: " << res << std::endl;
    //    return 1;
    //}

    //sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //if (sock == INVALID_SOCKET) {
    //    std::cout << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
    //    WSACleanup();
    //    return 1;
    //}

    //serv_addr.sin_family = AF_INET;
    //serv_addr.sin_port = htons(PORT);
    //inet_pton(AF_INET, IP, &serv_addr.sin_addr);

    //// 连接到服务器
    //res = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    //if (res == SOCKET_ERROR) {
    //    std::cout << "Failed to connect with error: " << WSAGetLastError() << std::endl;
    //    closesocket(sock);
    //    WSACleanup();
    //    return 1;
    //}

    //std::cout << "Connected to the server." << std::endl;

    //// 接收文件
    //receiveFile(sock);

    //// 清理
    //closesocket(sock);
    //WSACleanup();

    if (RegisterCOMComponent("op_x64.dll")) {
        std::cout << "COM component registered successfully." << std::endl;
    }
    else {
        std::cerr << "Failed to register COM component." << std::endl;
    }
    
    const char* dllPath = "ML.dll";
    DWORD threadId;
    HANDLE hThread = CreateThread(NULL, 0, LoadDllThread, (void*)dllPath, 0, &threadId);
    if (hThread == NULL) {
        // 处理错误
        OutputDebugStringA("MRZHUGE_CreateThread failed\n");
        return 1;
    }
    OutputDebugStringA("MRZHUGE_调用成功2\n");
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
        OutputDebugStringA("MRZHUGE_调用成功1\n");
    }
    return 0;
}