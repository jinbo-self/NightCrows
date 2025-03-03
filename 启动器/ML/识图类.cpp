#include "pch.h"
#include "识图类.h"


void 识图类::初始化()
{
    hDCScreen = GetDC(NULL);
    if (!hDCScreen) {
        return; // 如果获取DC失败，则返回无效颜色
    }
}

std::array<BYTE, 3> 识图类::识别颜色(识图坐标 坐标)
{
    // 获取设备上下文（DC）用于整个屏幕
    

    // 获取指定点的颜色
    COLORREF color = GetPixel(hDCScreen, 坐标.x, 坐标.y);

    std::array<BYTE, 3> colorArray;
    ColorRefToArray(color, colorArray);
    return colorArray;
}
void 识图类::ColorRefToArray(COLORREF color, std::array<BYTE, 3>& arr)
{
    arr[0] = GetRValue(color); // 提取红色分量
    arr[1] = GetGValue(color); // 提取绿色分量
    arr[2] = GetBValue(color); // 提取蓝色分量
}

bool 识图类::isAuto()
{
    std::array<BYTE, 3> Auto1 = 识别颜色(Auto坐标1);
    std::array<BYTE, 3> Auto2 = 识别颜色(Auto坐标2);
    if ((Auto1[0] > Auto坐标1.颜色[0] && Auto1[1] > Auto坐标1.颜色[1] && Auto1[2] > Auto坐标1.颜色[2])
        && (Auto2[0] > Auto坐标1.颜色[0] && Auto2[1] > Auto坐标1.颜色[1] && Auto2[2] > Auto坐标1.颜色[2])) {
        return true;
    }
    return false;
}

bool 识图类::isQuest()
{
    std::array<BYTE, 3> Auto1 = 识别颜色(Quest坐标1);
    std::array<BYTE, 3> Auto2 = 识别颜色(Quest坐标2);
    if ((Auto1[0] > Quest坐标1.颜色[0] && Auto1[1] > Quest坐标1.颜色[1] && Auto1[2] > Quest坐标1.颜色[2])
        && (Auto2[0] > Quest坐标2.颜色[0] && Auto2[1] > Quest坐标2.颜色[1] && Auto2[2] > Quest坐标2.颜色[2])) {
        return true;
    }
    return false;
}

bool 识图类::查找跳过()
{
    return false;
}

bool 识图类::查找装备穿戴()
{
    return false;
}
//生命力药水 = { 909,713,{159,18,13} };
bool 识图类::生命力药水用完()
{
    std::array<BYTE, 3> 三色 = 识别颜色(生命力药水);
    if (三色[0] <100) {
        return true;
    }
    return false;
}

bool 识图类::查找大地图据点()
{
    int dis = 20;
    std::array<BYTE, 3> Auto1 = 识别颜色(据点1);
    std::array<BYTE, 3> Auto2 = 识别颜色(据点2);
    if ((Auto1[0] > 据点1.颜色[0]- dis && Auto1[0] < 据点1.颜色[0] + dis
        && Auto1[1] > 据点1.颜色[1]- dis && Auto1[1] < 据点1.颜色[1] + dis
        && Auto1[2] > 据点1.颜色[2]- dis && Auto1[2] < 据点1.颜色[2]+ dis)
        && (Auto2[0] > 据点2.颜色[0]- dis && Auto2[0] < 据点2.颜色[0]+ dis
            && Auto2[1] > 据点2.颜色[1]- dis && Auto2[1] < 据点2.颜色[1]+ dis
            && Auto2[2] > 据点2.颜色[2]-dis && Auto2[2] < 据点2.颜色[2]+dis)) {
        return true;
    }
    return false;
}

bool 识图类::通行证可领取()
{
    std::array<BYTE, 3> Auto1 = 识别颜色(通行证);
    if (Auto1[0] > 200) {
        return true;
    }
    return false;
}

bool 识图类::查找菜单红点()
{
    std::array<BYTE, 3> Auto1 = 识别颜色(菜单红点);
    if (Auto1[0] > 200) {
        return true;
    }
    return false;
}

bool 识图类::查找成就红点()
{
    std::array<BYTE, 3> Auto1 = 识别颜色(成就红点);
    if (Auto1[0] > 200) {
        return true;
    }
    return false;
}

bool 识图类::查找强化最大安全阶段()
{
    std::array<BYTE, 3> Auto1 = 识别颜色(强化最大安全阶段);
    if (Auto1[0] > 100 && Auto1[1]>100) {
        return true;
    }
    return false;
}

bool 识图类::查找邮箱红点()
{
    std::array<BYTE, 3> Auto1 = 识别颜色(邮箱红点);
    if (Auto1[0] > 200) {
        return true;
    }
    return false;
}

bool 识图类::查找信念传承红点()
{
    std::array<BYTE, 3> Auto1 = 识别颜色(信念传承红点);
    if (Auto1[0] > 200) {
        return true;
    }
    return false;
}

bool 识图类::查找收藏红点()
{
    std::array<BYTE, 3> Auto1 = 识别颜色(收藏红点);
    if (Auto1[0] > 200) {
        return true;
    }
    return false;
}

bool 识图类::查找坐骑红点()
{
    std::array<BYTE, 3> Auto1 = 识别颜色(坐骑红点);
    if (Auto1[0] > 200) {
        return true;
    }
    return false;
}

bool 识图类::查找武器外形红点()
{
    std::array<BYTE, 3> Auto1 = 识别颜色(武器外形红点);
    if (Auto1[0] > 200) {
        return true;
    }
    return false;
}

bool 识图类::检查范围内颜色(int x, int y, int width, int height, std::array<BYTE, 3>& color,int dis)
{
    //大于像素就输出
    // 创建一个与屏幕设备上下文兼容的内存设备上下文
    HDC hMemoryDC = CreateCompatibleDC(hDCScreen);
    // 创建一个位图
    HBITMAP hBitmap = CreateCompatibleBitmap(hDCScreen, width, height);
    // 将位图选入内存设备上下文中
    SelectObject(hMemoryDC, hBitmap);
    // 将屏幕内容复制到内存设备上下文中
    BitBlt(hMemoryDC, 0, 0, width, height, hDCScreen, x, y, SRCCOPY);
    // 遍历区域内的每个像素,加快效率，每4个检查一次
    for (int i = 0; i < width; ) {
        for (int j = 0; j < height; ) {
            // 获取像素颜色
            COLORREF pixelColor = GetPixel(hMemoryDC, i, j);
            // 判断颜色是否匹配
            std::array<BYTE, 3> colorArray;
            ColorRefToArray(pixelColor, colorArray);
            if (colorArray[0] > color[0] || colorArray[1] > color[1] || colorArray[2] > color[2]) {
                // 清理资源
                DeleteObject(hBitmap);
                DeleteDC(hMemoryDC);
                return true;
            }
            j = j + dis;
        }
        i = i + dis;
    }
    // 清理资源
    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    return false;
}
