// CMainDialogWnd.cpp: 实现文件
//

#include "pch.h"
#include "ML.h"
#include "afxdialogex.h"
#include "CMainDialogWnd.h"

//#include "识字类.h"
// CMainDialogWnd 对话框

IMPLEMENT_DYNAMIC(CMainDialogWnd, CDialogEx)


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
    DDX_Control(pDX, tb_recx1, tb_recValuex1);
    DDX_Control(pDX, tb_recy1, tb_recValuey1);
    DDX_Control(pDX, tb_recx2, tb_recValuex2);
    DDX_Control(pDX, tb_recy2, tb_recValuey2);
    DDX_Control(pDX, IDC_EDIT5, 字符输出框);
    DDX_Control(pDX, IDC_EDIT6, 相似度);
}



BEGIN_MESSAGE_MAP(CMainDialogWnd, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMainDialogWnd::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CMainDialogWnd::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CMainDialogWnd::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CMainDialogWnd::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON4, &CMainDialogWnd::OnBnClickedButton4)
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


void CMainDialogWnd::OnBnClickedButton1()
{
    AfxBeginThread(MyLoopProc, NULL);

}


UINT MyLoopProc(LPVOID pParam)
{
    识字类 识字;
    键鼠类 键鼠;
    识图类 识图;


    识字.COM初始化();
    识图.初始化();
    int index = 0;
    int virtualKeys[4] = { 'W', 'A', 'S', 'D' };
    while (true) {
        Sleep(10);

        if (GetAsyncKeyState(VK_END) & 0x8000) {
            break;
        }

        if (识图.isAuto() || 识图.isQuest())
        {
            
            if (识字.查找装备穿戴()) {
                键鼠.移动鼠标((识字.装备穿戴.x1 + 识字.装备穿戴.x2) / 2, (识字.装备穿戴.y1 + 识字.装备穿戴.y2) / 2);
                Sleep(500);
                键鼠.点击鼠标左键();

            }
            if (识字.查找接受任务())
            {
                键鼠.移动鼠标((识字.接受任务.x1 + 识字.接受任务.x2) / 2, (识字.接受任务.y1 + 识字.接受任务.y2) / 2);
                键鼠.点击鼠标左键();
            }
            if (识图.通行证可领取())
            {
                通行证领取( 识字,  键鼠,  识图);
                成就领取(识字, 键鼠, 识图);
                邮箱领取(识字, 键鼠, 识图);
                每日商店领取(识字, 键鼠, 识图);
                开箱子(识字, 键鼠, 识图);
                强化装备(识字, 键鼠, 识图);
                坐骑外形装备(识字, 键鼠, 识图);
                武器外形装备(识字, 键鼠, 识图);
                收藏箱添加(识字, 键鼠, 识图);
                信念传承(识字, 键鼠, 识图);
            }
            std::array<BYTE, 3> 检测色块 = { 200,200,200 };//百位和千位的血瓶数量
            if (识图.生命力药水用完()&& !识图.检查范围内颜色(901, 711, 16, 13, 检测色块, 3)
                &&识字.查找快捷栏药品数量()<100)
            {
                买药(识字, 键鼠, 识图);//低于100就买药
            }
            
        }
        if (识图.isQuest()) {
            std::array<BYTE, 3> 残血 = 识图.识别颜色({ 109,712 });
            if (残血[0] < 100)  //血条掉到一半以下
            {
                if (!识字.查找死亡骑士())
                {
                    //绕圈打法回血 ,死亡骑士直接锁定,还是别走位浪费输出时间了
                    键鼠.按下按键(virtualKeys[index % 4], 5000);
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

            std::array<BYTE, 3> 残血 = 识图.识别颜色({ 142,709 });
            if (残血[0] < 100)  //血条掉到一半以下
            {
                //绕圈打法回血
                OutputDebugString(L"回血\n");
                while (识图.识别颜色({ 188,711 })[0] < 100) {
                    if (GetAsyncKeyState(VK_END) & 0x8000) {
                        break;
                    }
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

            continue;
        }
        else
        {
            if (识字.查找跳过()) {
                键鼠.移动鼠标((识字.跳过.x1 + 识字.跳过.x2) / 2, (识字.跳过.y1 + 识字.跳过.y2) / 2);
                键鼠.点击鼠标左键();
                Sleep(500);
                键鼠.移动鼠标(614, 352);
            }

            /*滑翔翼，坐骑穿戴*/
            if (识字.查找穿戴()) {
                键鼠.移动鼠标((识字.穿戴.x1 + 识字.穿戴.x2) / 2, (识字.穿戴.y1 + 识字.穿戴.y2) / 2);
                键鼠.点击鼠标左键();
                Sleep(1000);
                键鼠.按下按键(VK_ESCAPE);
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
            if (识字.查找节电模式()) {
                键鼠.按下按键('L');
            }
            if (识字.查找复活()) {
                键鼠.移动鼠标((识字.复活.x1 + 识字.复活.x2) / 2, (识字.复活.y1 + 识字.复活.y2) / 2);
                键鼠.点击鼠标左键();
                Sleep(2000);//等待传送
                //重新整理状态，上buff
                //先判断是不是主界面
                if (!(识图.isQuest() || 识图.isAuto())) {
                    键鼠.按下按键(VK_ESCAPE);
                }
                Sleep(1000);
                买药(识字, 键鼠, 识图);
                Sleep(1000);
                买技能书(识字, 键鼠, 识图);
                Sleep(1000);
                持续技能开启(识字, 键鼠, 识图);
                Sleep(1000);
                穿戴装备(识字, 键鼠, 识图);
                Sleep(1000);
                学习和摆放技能(识字, 键鼠, 识图);
                Sleep(1000);
                嗑状态药(识字, 键鼠, 识图);
                Sleep(1000);
                

                通行证领取(识字, 键鼠, 识图);
                成就领取(识字, 键鼠, 识图);
                邮箱领取(识字, 键鼠, 识图);
                每日商店领取(识字, 键鼠, 识图);
                开箱子(识字, 键鼠, 识图);
                强化装备(识字, 键鼠, 识图);
                坐骑外形装备(识字, 键鼠, 识图);
                武器外形装备(识字, 键鼠, 识图);
                收藏箱添加(识字, 键鼠, 识图);
                信念传承(识字, 键鼠, 识图);
            }
            if (识字.查找结束游戏())
            {
                键鼠.按下按键(VK_ESCAPE);
            }
            if (识字.查找职业())
            {
                Sleep(1000);
                键鼠.移动鼠标(143, 183);
                键鼠.点击鼠标左键();
                Sleep(1000);
                键鼠.移动鼠标(110, 716);
                键鼠.点击鼠标左键();
                Sleep(1000);
                键鼠.按下按键('Y');
                Sleep(1000);
                键鼠.按下按键(VK_ESCAPE);
            }
        }


    }

    return 0;
}

void CMainDialogWnd::OnBnClickedButton2()
{
    // TODO: 在此添加控件通知处理程序代码
    Sleep(5000);
    键鼠类 键鼠;
    键鼠.按下按键('I');
}


void CMainDialogWnd::OnBnClickedButton3()
{
    // TODO: 在此添加控件通知处理程序代码
    识字类 识字;
    识字.COM初始化();
    识字.获取字符(识字.装备穿戴);

    CString strx1;
    CString stry1;
    CString strx2;
    CString stry2;
    CString sim;
    UpdateData(TRUE); // 将数据从控件同步到变量
    tb_recValuex1.GetWindowText(strx1);
    tb_recValuey1.GetWindowText(stry1);
    tb_recValuex2.GetWindowText(strx2);
    tb_recValuey2.GetWindowText(stry2);
    相似度.GetWindowText(sim);

    double siml = _tstof(sim);
    int nx1 = _ttoi(strx1);
    int ny1 = _ttoi(stry1);
    int nx2 = _ttoi(strx2);
    int ny2 = _ttoi(stry2);

    std::wstring output = 识字.获取字符({ nx1 ,ny1 ,nx2 ,ny2 }, siml);
    字符输出框.SetWindowTextW(output.c_str());
}


void CMainDialogWnd::OnBnClickedButton4()
{
    // TODO: 在此添加控件通知处理程序代码
    识字类 识字;
    键鼠类 键鼠;
    识图类 识图;


    识字.COM初始化();
    识图.初始化();
    Sleep(5000);
    //穿戴装备(识字, 键鼠, 识图);
    //学习和摆放技能(识字, 键鼠, 识图);
    //买药(识字, 键鼠, 识图);
    /*通行证领取(识字, 键鼠, 识图);*/
    //成就领取(识字, 键鼠, 识图);
    /*开箱子(识字, 键鼠, 识图);*/
    //强化装备(识字, 键鼠, 识图);
    //邮箱领取(识字, 键鼠, 识图);
    //每日商店领取(识字, 键鼠, 识图);
    //信念传承(识字, 键鼠, 识图);
    持续技能开启(识字, 键鼠, 识图);
}
