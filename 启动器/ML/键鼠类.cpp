#include "pch.h"
#include "键鼠类.h"
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
void 键鼠类::点击鼠标左键()
{
	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &Input, sizeof(INPUT));
	
	ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &Input, sizeof(INPUT));
}

void 键鼠类::移动鼠标(int x, int y)
{
	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = x * (65536 / GetSystemMetrics(SM_CXSCREEN)); // 将x映射到[0, 65535]
	Input.mi.dy = y * (65536 / GetSystemMetrics(SM_CYSCREEN)); // 将y映射到[0, 65535]
	SendInput(1, &Input, sizeof(INPUT));

}

void 键鼠类::按下按键(WORD key,int delay)
{
	INPUT Input = { 0 };
	Input.type = INPUT_KEYBOARD;
	Input.ki.wVk = key;

	DWORD startTime = GetTickCount64();
	while (GetTickCount64() - startTime < (DWORD)delay) {
		// 模拟按键按下
		Input.ki.dwFlags = 0; // 没有特殊标志，表示按下按键
		SendInput(1, &Input, sizeof(INPUT));

		// 微小延时来模拟长按而不是连续点击
		Sleep(10); // 这里的延时可以根据需要调整

	}

	Input.ki.dwFlags = KEYEVENTF_KEYUP; // 按键释放
	SendInput(1, &Input, sizeof(INPUT));
}
