#include "pch.h"
#include "������.h"
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
void ������::���������()
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

void ������::�ƶ����(int x, int y)
{
	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = x * (65536 / GetSystemMetrics(SM_CXSCREEN)); // ��xӳ�䵽[0, 65535]
	Input.mi.dy = y * (65536 / GetSystemMetrics(SM_CYSCREEN)); // ��yӳ�䵽[0, 65535]
	SendInput(1, &Input, sizeof(INPUT));

}

void ������::���°���(WORD key,int delay)
{
	INPUT Input = { 0 };
	Input.type = INPUT_KEYBOARD;
	Input.ki.wVk = key;

	DWORD startTime = GetTickCount64();
	while (GetTickCount64() - startTime < (DWORD)delay) {
		// ģ�ⰴ������
		Input.ki.dwFlags = 0; // û�������־����ʾ���°���
		SendInput(1, &Input, sizeof(INPUT));

		// ΢С��ʱ��ģ�ⳤ���������������
		Sleep(10); // �������ʱ���Ը�����Ҫ����

	}

	Input.ki.dwFlags = KEYEVENTF_KEYUP; // �����ͷ�
	SendInput(1, &Input, sizeof(INPUT));
}
