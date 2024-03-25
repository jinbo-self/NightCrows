#pragma once
#include "afxdialogex.h"

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
};
