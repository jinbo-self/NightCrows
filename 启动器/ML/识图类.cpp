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

    // �ͷ��豸������
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
