#pragma once

#include "afxdialogex.h"
#include <memory>
#include"键鼠类.h"
#include"识图类.h"
#include "识字类.h"
//将类作为导出类
#ifndef DLLEXPORY
#define DLL_EXPORY _declspec(dllimport)
#else
#define DLL_EXPORY _declspec(dllexport)
#endif
#include "resource.h"

// CMainDialogWnd 对话框

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
	BOOL CMainDialogWnd::PreTranslateMessage(MSG* pMsg)
	{
		if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		{
			// 屏蔽ESC键消息
			return TRUE;
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
void 穿戴装备(识字类 识字, 键鼠类 键鼠, 识图类 识图);
/*主动技能摆放*/
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