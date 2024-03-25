#pragma once
#include<windows.h>
class 键鼠类
{
public:
	void 点击鼠标左键();
public:
	void 移动鼠标(int x, int y);
public:
	void 按下按键(WORD key,int delay=1000);
};

