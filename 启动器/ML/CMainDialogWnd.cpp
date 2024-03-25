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
//主线程
UINT MyLoopProc(LPVOID pParam);
void 穿戴装备(识字类 识字,键鼠类 键鼠,识图类 识图);
void 学习和摆放技能(识字类 识字, 键鼠类 键鼠, 识图类 识图);
void 嗑状态药(识字类 识字, 键鼠类 键鼠, 识图类 识图);

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
        
        if (GetAsyncKeyState(VK_END)& 0x8000) {
            break;
        }
        if ((识图.isQuest() || 识图.isAuto()))
        {
            //if (识图.生命力药水用完())
            //{
            //    if (识字.查找小地图_阿维利乌斯城堡())
            //    {
            //        键鼠.移动鼠标(249, 91);
            //        键鼠.点击鼠标左键();
            //        Sleep(1000);
            //        键鼠.移动鼠标((识字.小地图_杂货.x1 + 识字.小地图_杂货.x2) / 2, (识字.小地图_杂货.y1 + 识字.小地图_杂货.y2) / 2);
            //        键鼠.点击鼠标左键();
            //    }
            //    else
            //    {
            //        键鼠.按下按键('M');//打开地图传送回去买药
            //        键鼠.移动鼠标(1056, 198);

            //    }


            //}
           
        }
        if (识图.isQuest()) {
            std::array<BYTE, 3> 残血 = 识图.识别颜色({ 109,712 });
            if (残血[0] < 100)  //血条掉到一半以下
            {
                if (!识字.查找死亡骑士())
                {
                    //绕圈打法回血 ,死亡骑士直接锁定,还是别走完浪费输出时间了
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
                穿戴装备(识字, 键鼠, 识图);
                学习和摆放技能(识字, 键鼠, 识图);
                嗑状态药(识字, 键鼠, 识图);
            }

        }
        

    }

    return 0;
}

void 穿戴装备(识字类 识字, 键鼠类 键鼠, 识图类 识图)
{
    if (!识字.查找背包())
    {
        键鼠.按下按键('I');
    }
    
    //背包左右间距54 996，137；1050，137；1104，137；1158，137  》190
    //上下间距54，137，191，245，299
    Sleep(1000);
    键鼠.移动鼠标(1247, 210); //装备栏
    键鼠.点击鼠标左键();
    Sleep(100);
    键鼠.移动鼠标(1188, 636);//整理背包
    键鼠.点击鼠标左键();
    Sleep(1000);
    识图坐标 背包E起始 = { 996,137,{204,183,142} };
    //先脱下所有装备
    int 背包装备x[4] = {1017,1069,1127,1178}; //直接记录一行的位置
    while (识字.查找背包() && 识图.识别颜色(背包E起始)[0]>190)
    {
        for (int index = 0; index < 4; index++)
        {
            int 背包x = 背包装备x[index];
            if (识图.识别颜色({ 背包E起始.x+ index*54,137 })[0] > 190)
            {
                键鼠.移动鼠标(背包x, 137);
                键鼠.点击鼠标左键();
                Sleep(200);
                键鼠.点击鼠标左键();
                Sleep(1500);
            }
            
            
        }
        键鼠.移动鼠标(1188, 636);//整理背包
        键鼠.点击鼠标左键();
        Sleep(1500);
    }
    
    //计算装备数量
    int index = 0;
    识图坐标 背包起始 = { 1004,140 };//25*25
    int 装备数量 = 0;
    while (识字.查找背包())
    {
        int 背包y = 背包起始.y + index * 54;
        bool 跳出 = false;
        for (size_t i = 0; i < 4; i++)
        {
            int 背包x = 背包起始.x + i * 54;
            std::array<BYTE, 3> 检测色块 = { 60,60,60 };
            if (!识图.检查范围内颜色(背包x, 背包y, 25, 25, 检测色块))
            {
                装备数量 = index * 4 + i;
                跳出 = true; 
                break;
            } 
        }
        if (跳出)
        {
            break;
        }
        index++;
    }
    OutputDebugString(std::to_wstring(装备数量).c_str());
    //从尾部开始穿戴
    OutputDebugString(L"从尾部开始穿戴\n");
    //第一个装备还是需要穿戴
    背包起始 = { 1019,155 };//25*25
    while (装备数量 > -1)
    {
        int 行号 = 装备数量 / 4;//13/4=3...1  12/4=3...0
        int 列号 = 装备数量 % 4;
        识图坐标 坐标 = {背包起始.x + 列号 *54,背包起始.y + 行号*54 };
        键鼠.移动鼠标(坐标.x, 坐标.y);
        键鼠.点击鼠标左键();
        Sleep(500);
        键鼠.点击鼠标左键();
        Sleep(1500);
        装备数量--;
    }
    if (识字.查找背包())
    {
        键鼠.按下按键('I');
    }
}

void 学习和摆放技能(识字类 识字, 键鼠类 键鼠, 识图类 识图)
{
    //学习技能
    if (!识字.查找背包())
    {
        键鼠.按下按键('I');
    }
    Sleep(500);
    键鼠.移动鼠标(1248, 277); //背包藏品栏
    键鼠.点击鼠标左键();
    Sleep(500);
    键鼠.移动鼠标(1188, 636);//整理背包
    键鼠.点击鼠标左键();
    Sleep(500);
    int index = 0;
    识图坐标 背包起始 = { 1004,140 };//25*25
    int 物品数量 = 0;

    //查找背包,学习技能
    while (识字.查找背包())
    {
        int 背包y = 背包起始.y + index * 54;
        bool 跳出 = false;
        for (size_t i = 0; i < 4; i++)
        {
            int 背包x = 背包起始.x + i * 54;
            std::array<BYTE, 3> 检测色块 = { 60,60,60 };
            if (!识图.检查范围内颜色(背包x, 背包y, 25, 25, 检测色块))
            {
                物品数量 = index * 4 + i;
                跳出 = true;
                break;
            }
            else
            {
                键鼠.移动鼠标(背包x, 背包y);
                键鼠.点击鼠标左键();
                Sleep(1000);
                if (识字.查找背包技能书说明())
                {
                    键鼠.点击鼠标左键();
                    Sleep(1000);
                }
            }
        }
        if (跳出)
        {
            break;
        }
        index++;
    }
    
    //摆放技能
    if (!识字.查找主动技能())
    {
        键鼠.按下按键('K');
    }
    Sleep(500);
    键鼠.移动鼠标(1243, 147); //主动技能栏
    键鼠.点击鼠标左键();

    Sleep(500);
    键鼠.移动鼠标(1036, 638); //技能排序
    键鼠.点击鼠标左键();

    Sleep(500);
    if (!识字.查找技能排序自动释放())
    {
        键鼠.移动鼠标((识字.技能排序自动释放.x1 + 识字.技能排序自动释放.x2) / 2, (识字.技能排序自动释放.y1 + 识字.技能排序自动释放.y2) / 2);
        键鼠.点击鼠标左键();
    }
    //反复释放
    if (识图.识别颜色({ 37,649 })[0] < 100 && 识图.识别颜色({ 37,649 })[1] < 100&& 识图.识别颜色({ 37,649 })[2] < 100)
    {
        Sleep(500);
        键鼠.移动鼠标(37, 649);
        键鼠.点击鼠标左键();
    }
    //PVP释放
    if (识图.识别颜色({ 157,649 })[0] < 100 && 识图.识别颜色({ 157,649 })[1] < 100 && 识图.识别颜色({ 157,649 })[2] < 100)
    {
        Sleep(500);
        键鼠.移动鼠标(157, 649);
        键鼠.点击鼠标左键();
    }
    //跳过无法释放的技能
    if (识图.识别颜色({ 37,679 })[0] < 100 && 识图.识别颜色({ 37,679 })[1] < 100 && 识图.识别颜色({ 37,679 })[2] < 100)
    {
        Sleep(500);
        键鼠.移动鼠标(37, 679);
        键鼠.点击鼠标左键();
    }
    //猎人开启决心
    if (!识字.查找猎人_决心技能自动开启()) {
        Sleep(500);
        键鼠.移动鼠标((识字.猎人_决心技能自动开启.x1 + 识字.猎人_决心技能自动开启.x2) / 2, (识字.猎人_决心技能自动开启.y1 + 识字.猎人_决心技能自动开启.y2) / 2);
        键鼠.点击鼠标左键();
    }

    //重置技能
    Sleep(500);
    键鼠.移动鼠标(96,714);
    键鼠.点击鼠标左键();
    Sleep(500);
    键鼠.按下按键('Y');
    Sleep(500);
    //放置技能1
    键鼠.移动鼠标(1010,162);
    键鼠.点击鼠标左键();
    Sleep(500);
    键鼠.点击鼠标左键();
    Sleep(500);
    //放置技能2
    键鼠.移动鼠标(1010, 222);
    键鼠.点击鼠标左键();
    Sleep(500);
    键鼠.点击鼠标左键();
    Sleep(500);
    //放置技能3
    键鼠.移动鼠标(1010, 288);
    键鼠.点击鼠标左键();
    Sleep(500);
    键鼠.点击鼠标左键();
    Sleep(500);
    //放置技能4
    键鼠.移动鼠标(1010, 352);
    键鼠.点击鼠标左键();
    Sleep(500);
    键鼠.点击鼠标左键();
    Sleep(500);
    //完成放置
    键鼠.移动鼠标(1033, 637);
    键鼠.点击鼠标左键();
    Sleep(500);

    //关闭技能栏
    if (识字.查找主动技能())
    {
        键鼠.按下按键('K');
    }
}

void 嗑状态药(识字类 识字, 键鼠类 键鼠, 识图类 识图)
{
    if (!识字.查找背包())
    {
        键鼠.按下按键('I');
    }
    键鼠.移动鼠标(1245,338);
    键鼠.点击鼠标左键();
    Sleep(1000);

    //背包遍历
    int index = 0;
    识图坐标 背包起始 = { 1004,140 };//25*25
    int 物品数量 = 0;
    while (识字.查找背包())
    {
        int 背包y = 背包起始.y + index * 54;
        bool 跳出 = false;
        for (size_t i = 0; i < 4; i++)
        {
            int 背包x = 背包起始.x + i * 54;
            std::array<BYTE, 3> 检测色块 = { 60,60,60 };
            //没检测到就是空的背包栏
            if (!识图.检查范围内颜色(背包x, 背包y, 25, 25, 检测色块))
            {
                物品数量 = index * 4 + i;
                跳出 = true;
                break;
            }
            else
            {
                键鼠.移动鼠标(背包x, 背包y);
                键鼠.点击鼠标左键();
                Sleep(1000);
                键鼠.点击鼠标左键();
                Sleep(1000);
            }
        }
        if (跳出)
        {
            break;
        }
        index++;
    }
    if (!识字.查找背包())
    {
        键鼠.按下按键('I');
    }

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
    UpdateData(TRUE); // 将数据从控件同步到变量
    tb_recValuex1.GetWindowText(strx1);
    tb_recValuey1.GetWindowText(stry1);
    tb_recValuex2.GetWindowText(strx2);
    tb_recValuey2.GetWindowText(stry2);

    int nx1 = _ttoi(strx1);
    int ny1 = _ttoi(stry1);
    int nx2 = _ttoi(strx2);
    int ny2 = _ttoi(stry2);

    std::wstring output = 识字.获取字符({ nx1 ,ny1 ,nx2 ,ny2 });
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
    学习和摆放技能(识字, 键鼠, 识图);
}
