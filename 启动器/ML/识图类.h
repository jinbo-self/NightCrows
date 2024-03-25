#pragma once
#include <windows.h>
#include <array>

struct 识图坐标
{
	int x,y;
	std::array<BYTE, 3> 颜色;
};
class 识图类
{
private:
	HDC hDCScreen;//249,190,145
	识图坐标 Auto坐标1 = { 1226,537,{200,190,145} };
	识图坐标 Auto坐标2 = { 1241,539,{200,190,145} };
	识图坐标 Quest坐标1 = { 1223,538,{200,190,145} };
	识图坐标 Quest坐标2 = { 1249,540,{200,190,145} };
	识图坐标 生命力药水 = { 909,713,{159,18,13} };
	识图坐标 跳过1 = {};
	识图坐标 跳过2 = {};
	识图坐标 装备穿戴1 = {};
	识图坐标 装备穿戴2 = {};
public:
	void 初始化();
	std::array<BYTE, 3> 识别颜色(识图坐标 坐标);
	bool isAuto();
	bool isQuest();
	bool 查找跳过();
	bool 查找装备穿戴();
	bool 生命力药水用完();
	bool 检查范围内颜色(int x, int y, int width, int height, std::array<BYTE, 3> &color);
private:
	void ColorRefToArray(COLORREF color, std::array<BYTE, 3>& arr);
	
};

