﻿#pragma once

#include "afxdialogex.h"
#include <memory>
#include"键鼠类.h"
#include"识图类.h"
#include "识字类.h"
#include <atomic>
#include <iostream>
#include <fstream>
#include <vector>
#include <codecvt>
#include <sstream>
#include <filesystem>
//将类作为导出类
#ifndef DLLEXPORY
#define DLL_EXPORY _declspec(dllimport)
#else
#define DLL_EXPORY _declspec(dllexport)
#endif
#include "resource.h"
#include <vector>
struct 角色配置 {
	std::wstring 名字;
	int 等级;
	bool 是否刷完;
	bool 正在刷;
};
// CMainDialogWnd 对话框
extern std::atomic<bool> running;
class DLL_EXPORY CMainDialogWnd : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDialogWnd)

public:
	
	CMainDialogWnd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMainDialogWnd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	//重写消息
	BOOL CMainDialogWnd::PreTranslateMessage(MSG* pMsg)
	{
		if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		{
			// 屏蔽ESC键消息
			return TRUE;
		}
		if (pMsg->message == WM_KEYDOWN)
		{
			switch (pMsg->wParam)
			{
			case VK_END: // 检查F1键
				OnBnClickedButton2();
				return TRUE;
				// 添加其他按键处理
			}
		}
		return CDialogEx::PreTranslateMessage(pMsg);
	}
	// 左上角坐标x
	CEdit tb_recValuex1;
	CEdit tb_recValuey1;
	CEdit tb_recValuex2;
	CEdit tb_recValuey2;
	CEdit 字符输出框;
	afx_msg void OnBnClickedButton4();
	CEdit 相似度;
};
//主线程
UINT MyLoopProc(LPVOID pParam);
UINT 刷副本线程(LPVOID pParam);
void 穿戴装备(识字类 识字, 键鼠类 键鼠, 识图类 识图);
/*主动技能摆放,弓箭手会开启决心*/
void 学习和摆放技能(识字类 识字, 键鼠类 键鼠, 识图类 识图);
void 持续技能开启(识字类 识字, 键鼠类 键鼠, 识图类 识图);
void 嗑状态药(识字类 识字, 键鼠类 键鼠, 识图类 识图);
void 买药(识字类 识字, 键鼠类 键鼠, 识图类 识图);
void 买技能书(识字类 识字, 键鼠类 键鼠, 识图类 识图);

void 通行证领取(识字类 识字, 键鼠类 键鼠, 识图类 识图);
void 成就领取(识字类 识字, 键鼠类 键鼠, 识图类 识图);
void 邮箱领取(识字类 识字, 键鼠类 键鼠, 识图类 识图);
void 每日商店领取(识字类 识字, 键鼠类 键鼠, 识图类 识图);
void 开箱子(识字类 识字, 键鼠类 键鼠, 识图类 识图);
void 强化装备(识字类 识字, 键鼠类 键鼠, 识图类 识图);
void 坐骑外形装备(识字类 识字, 键鼠类 键鼠, 识图类 识图);
void 武器外形装备(识字类 识字, 键鼠类 键鼠, 识图类 识图);
void 收藏箱添加(识字类 识字, 键鼠类 键鼠, 识图类 识图);
void 信念传承(识字类 识字, 键鼠类 键鼠, 识图类 识图);

// 定义函数原型
typedef NTSTATUS(NTAPI* pRtlGetVersion)(LPOSVERSIONINFOEXW);

// 获取操作系统版本
bool GetOSVersion(DWORD& dwMajor, DWORD& dwMinor, DWORD& dwBuildNumber);
//调整窗口大小
void AdjustWindow(HWND hWnd, int clientWidth, int clientHeight, int clientX, int clientY);

std::vector<角色配置> 读取角色配置(const std::string& 文件名);
void 写入角色配置(const std::string& 文件名, const std::vector<角色配置>& 角色数组);