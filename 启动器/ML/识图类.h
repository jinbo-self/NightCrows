#pragma once
#include <windows.h>
#include <array>

struct ʶͼ����
{
	int x,y;
	std::array<BYTE, 3> ��ɫ;
};
class ʶͼ��
{
private:
	HDC hDCScreen;//249,190,145
	ʶͼ���� Auto����1 = { 1226,537,{200,190,145} };
	ʶͼ���� Auto����2 = { 1241,539,{200,190,145} };
	ʶͼ���� Quest����1 = { 1223,538,{200,190,145} };
	ʶͼ���� Quest����2 = { 1249,540,{200,190,145} };
	ʶͼ���� ������ҩˮ = { 909,713,{159,18,13} };
	ʶͼ���� ����1 = {};
	ʶͼ���� ����2 = {};
	ʶͼ���� װ������1 = {};
	ʶͼ���� װ������2 = {};
public:
	void ��ʼ��();
	std::array<BYTE, 3> ʶ����ɫ(ʶͼ���� ����);
	bool isAuto();
	bool isQuest();
	bool ��������();
	bool ����װ������();
	bool ������ҩˮ����();
	bool ��鷶Χ����ɫ(int x, int y, int width, int height, std::array<BYTE, 3> &color);
private:
	void ColorRefToArray(COLORREF color, std::array<BYTE, 3>& arr);
	
};

