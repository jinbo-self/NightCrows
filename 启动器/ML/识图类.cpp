#include "pch.h"
#include "ʶͼ��.h"


void ʶͼ��::��ʼ��()
{
    hDCScreen = GetDC(NULL);
    if (!hDCScreen) {
        return; // �����ȡDCʧ�ܣ��򷵻���Ч��ɫ
    }
}

std::array<BYTE, 3> ʶͼ��::ʶ����ɫ(ʶͼ���� ����)
{
    // ��ȡ�豸�����ģ�DC������������Ļ
    

    // ��ȡָ�������ɫ
    COLORREF color = GetPixel(hDCScreen, ����.x, ����.y);

    std::array<BYTE, 3> colorArray;
    ColorRefToArray(color, colorArray);
    return colorArray;
}
void ʶͼ��::ColorRefToArray(COLORREF color, std::array<BYTE, 3>& arr)
{
    arr[0] = GetRValue(color); // ��ȡ��ɫ����
    arr[1] = GetGValue(color); // ��ȡ��ɫ����
    arr[2] = GetBValue(color); // ��ȡ��ɫ����
}

bool ʶͼ��::isAuto()
{
    std::array<BYTE, 3> Auto1 = ʶ����ɫ(Auto����1);
    std::array<BYTE, 3> Auto2 = ʶ����ɫ(Auto����2);
    if ((Auto1[0] > Auto����1.��ɫ[0] && Auto1[1] > Auto����1.��ɫ[1] && Auto1[2] > Auto����1.��ɫ[2])
        && (Auto2[0] > Auto����1.��ɫ[0] && Auto2[1] > Auto����1.��ɫ[1] && Auto2[2] > Auto����1.��ɫ[2])) {
        return true;
    }
    return false;
}

bool ʶͼ��::isQuest()
{
    std::array<BYTE, 3> Auto1 = ʶ����ɫ(Quest����1);
    std::array<BYTE, 3> Auto2 = ʶ����ɫ(Quest����2);
    if ((Auto1[0] > Quest����1.��ɫ[0] && Auto1[1] > Quest����1.��ɫ[1] && Auto1[2] > Quest����1.��ɫ[2])
        && (Auto2[0] > Quest����2.��ɫ[0] && Auto2[1] > Quest����2.��ɫ[1] && Auto2[2] > Quest����2.��ɫ[2])) {
        return true;
    }
    return false;
}

bool ʶͼ��::��������()
{
    return false;
}

bool ʶͼ��::����װ������()
{
    return false;
}
//������ҩˮ = { 909,713,{159,18,13} };
bool ʶͼ��::������ҩˮ����()
{
    std::array<BYTE, 3> ��ɫ = ʶ����ɫ(������ҩˮ);
    if (��ɫ[0] <100) {
        return true;
    }
    return false;
}

bool ʶͼ��::��鷶Χ����ɫ(int x, int y, int width, int height, std::array<BYTE, 3>& color)
{
    // ����һ������Ļ�豸�����ļ��ݵ��ڴ��豸������
    HDC hMemoryDC = CreateCompatibleDC(hDCScreen);
    // ����һ��λͼ
    HBITMAP hBitmap = CreateCompatibleBitmap(hDCScreen, width, height);
    // ��λͼѡ���ڴ��豸��������
    SelectObject(hMemoryDC, hBitmap);
    // ����Ļ���ݸ��Ƶ��ڴ��豸��������
    BitBlt(hMemoryDC, 0, 0, width, height, hDCScreen, x, y, SRCCOPY);
    // ���������ڵ�ÿ������,�ӿ�Ч�ʣ�ÿ4�����һ��
    for (int i = 0; i < width; ) {
        for (int j = 0; j < height; ) {
            // ��ȡ������ɫ
            COLORREF pixelColor = GetPixel(hMemoryDC, i, j);
            // �ж���ɫ�Ƿ�ƥ��
            std::array<BYTE, 3> colorArray;
            ColorRefToArray(pixelColor, colorArray);
            if (colorArray[0] > color[0] || colorArray[1] > color[1] || colorArray[2] > color[2]) {
                // ������Դ
                DeleteObject(hBitmap);
                DeleteDC(hMemoryDC);
                return true;
            }
            j = j + 4;
        }
        i = i + 4;
    }
    // ������Դ
    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    return false;
}
