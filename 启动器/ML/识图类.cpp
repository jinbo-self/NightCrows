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

    // 释放设备上下文
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
