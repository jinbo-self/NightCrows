// CMainDialogWnd.cpp: 实现文件
//

#include "pch.h"
#include "ML.h"
#include "afxdialogex.h"
#include "CMainDialogWnd.h"
#include <memory>
#include"键鼠类.h"
#include"识图类.h"
#include "识字类.h"
//#include "识字类.h"
// CMainDialogWnd 对话框

IMPLEMENT_DYNAMIC(CMainDialogWnd, CDialogEx)
UINT MyLoopProc(LPVOID pParam);
CMainDialogWnd::CMainDialogWnd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CMainDialogWnd::~CMainDialogWnd()
{
}

void CMainDialogWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(CMainDialogWnd, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMainDialogWnd::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CMainDialogWnd::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CMainDialogWnd::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CMainDialogWnd::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMainDialogWnd 消息处理程序
// CMLApp 初始化
CMainDialogWnd* PMainDialog;
extern "C" DLL_EXPORY DWORD ShowDialog(LPVOID lpParam) {
	std::unique_ptr<CMainDialogWnd> PMainDialog(new CMainDialogWnd);
	PMainDialog->DoModal();
	return TRUE;
}
void CMainDialogWnd::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
    //释放COM资源
    CoUninitialize();
	CDialogEx::OnOK();
}

bool g_bEndKeyPressed = false;
void CMainDialogWnd::OnBnClickedButton1()
{
    AfxBeginThread(MyLoopProc, NULL);

}

UINT MyLoopProc(LPVOID pParam)
{
    识字类 识字;
    键鼠类 键鼠;
    识图类 识图;

    g_bEndKeyPressed = true;

    识字.COM初始化();
    识图.初始化();
    int index = 0;
    int virtualKeys[4] = { 'W', 'A', 'S', 'D' };
    while (true) {
        Sleep(10);
        if (GetAsyncKeyState(VK_END)& 0x8000) {
            break;
        }

        if (识图.isQuest()) {
            std::array<BYTE, 3> 残血 = 识图.识别颜色({ 109,712 });
            if (残血[0] < 100)  //血条掉到一半以下
            {
                //绕圈打法回血
                OutputDebugString(L"走位\n");
                while (识图.识别颜色({ 188,711 })[0] < 100) {
                    键鼠.按下按键(virtualKeys[index %4], 5000);
                    index++;
                }
                

            }
            continue;
        }
        if (识图.isQuest() && 识图.isAuto())
        {
            OutputDebugStringA("错误识别\n");
            continue;
        }
        if (识图.isAuto()) {
            std::array<BYTE, 3> 残血 = 识图.识别颜色({ 109,712 });
            if (残血[0] < 100)  //血条掉到一半以下
            {
                //绕圈打法回血
                OutputDebugString(L"回血\n");
                while (识图.识别颜色({ 188,711 })[0] < 100) {
                    Sleep(1000);
                }


            }
            键鼠.移动鼠标(998, 115);
            键鼠.点击鼠标左键();
            Sleep(500);
            键鼠.按下按键('Y');
            if (识图.isAuto()) {
                键鼠.移动鼠标((识字.任务.x1 + 识字.任务.x2) / 2, (识字.任务.y1 + 识字.任务.y2) / 2);
                键鼠.点击鼠标左键();
                
            }
        }
        else
        {
            if (识字.查找跳过()) {
                键鼠.移动鼠标((识字.跳过.x1 + 识字.跳过.x2) / 2, (识字.跳过.y1 + 识字.跳过.y2) / 2);
                键鼠.点击鼠标左键();

            }

            /*滑翔翼，坐骑穿戴*/
            if (识字.查找穿戴()) {
                键鼠.移动鼠标((识字.穿戴.x1 + 识字.穿戴.x2) / 2, (识字.穿戴.y1 + 识字.穿戴.y2) / 2);
                键鼠.点击鼠标左键();
                Sleep(1000);
                键鼠.按下按键(VK_ESCAPE);
            }
            if (识图.查找装备穿戴()) {
                键鼠.移动鼠标((识字.装备穿戴.x1 + 识字.装备穿戴.x2) / 2, (识字.装备穿戴.y1 + 识字.装备穿戴.y2) / 2);
                键鼠.点击鼠标左键();
            }
            if (识字.查找装备穿戴()) {
                键鼠.移动鼠标((识字.装备穿戴.x1 + 识字.装备穿戴.x2) / 2, (识字.装备穿戴.y1 + 识字.装备穿戴.y2) / 2);
                键鼠.点击鼠标左键();

            }
            if (识字.查找武器外形穿戴()) {
                键鼠.移动鼠标((识字.武器外形穿戴.x1 + 识字.武器外形穿戴.x2) / 2, (识字.武器外形穿戴.y1 + 识字.武器外形穿戴.y2) / 2);
                键鼠.点击鼠标左键();
                Sleep(1000);
                键鼠.按下按键(VK_ESCAPE);
            }
            if (识字.查找添加()) {
                键鼠.移动鼠标((识字.添加.x1 + 识字.添加.x2) / 2, (识字.添加.y1 + 识字.添加.y2) / 2);
                键鼠.点击鼠标左键();
                键鼠.移动鼠标(1013, 197);//移动到翅膀处
                键鼠.点击鼠标左键();
            }
            if (识字.查找瞬间移动()) {
                键鼠.移动鼠标(709, 518);//移动到确认处
                键鼠.点击鼠标左键();
                Sleep(2000);
            }
            if (识字.查找购买()) {
                键鼠.移动鼠标(980, 214);//移动到关闭处
                键鼠.点击鼠标左键();
            }
            if (识字.查找请点击画面())
            {
                键鼠.移动鼠标((识字.请点击画面.x1 + 识字.请点击画面.x2) / 2, (识字.请点击画面.y1 + 识字.请点击画面.y2) / 2);
                键鼠.点击鼠标左键();
            }
        }
        

    }

    return 0;
}

void CMainDialogWnd::OnBnClickedButton2()
{
    // TODO: 在此添加控件通知处理程序代码
    g_bEndKeyPressed = true;
}


void CMainDialogWnd::OnBnClickedButton3()
{
    // TODO: 在此添加控件通知处理程序代码
    识字类 识字;
    识字.COM初始化();
    识字.获取字符(识字.装备穿戴);
}
