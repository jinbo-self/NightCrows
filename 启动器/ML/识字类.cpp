#include "pch.h"
#include "ʶ����.h"

HRESULT InvokeSafely(IDispatch* pDispatch, DISPID dispid, DISPPARAMS* pDispParams, VARIANT* pResult, EXCEPINFO* pExcepInfo, unsigned int* puArgErr) {
    if (pDispatch == nullptr || pDispParams == nullptr || pResult == nullptr || pExcepInfo == nullptr || puArgErr == nullptr) {
        // ����κ�һ�������ǿ�ָ�룬���ش����룬���� E_POINTER
        return -1;
    }
    __try {
        return pDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, pDispParams, pResult, pExcepInfo, puArgErr);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        // �����쳣�������¼��־�򷵻��ض��Ĵ�����
        return -1;
    }
}
HMODULE ʶ����::LoadDll()
{
	HMODULE hModule = LoadLibraryA("op_x64.dll");
	if (hModule == NULL) {
		// �������
		OutputDebugStringA(" failed load op_x64.dll:\n ");
	}/*
	libop opFunc = (libop)GetProcAddress(hModule, "libop");
	libop* op = opFunc();*/
	return hModule;
}


std::wstring ʶ����::��ȡ�ַ�(ʶ������ ����, DOUBLE sim)
{

    // ׼������OcrAuto
    DISPPARAMS dispparams;
    VARIANTARG varg[5];
    VariantInit(&varg[4]);
    varg[4].vt = VT_I4;
    varg[4].lVal = ����.x1;
    VariantInit(&varg[3]);
    varg[3].vt = VT_I4;
    varg[3].lVal = ����.y1;
    VariantInit(&varg[2]);
    varg[2].vt = VT_I4;
    varg[2].lVal = ����.x2;
    VariantInit(&varg[1]);
    varg[1].vt = VT_I4;
    varg[1].lVal = ����.y2;
    VariantInit(&varg[0]);
    varg[0].vt = VT_R8;
    varg[0].dblVal = sim;

    dispparams.rgvarg = varg;
    dispparams.cArgs = 5;
    dispparams.cNamedArgs = 0;

    VARIANT result;
    VariantInit(&result);
    EXCEPINFO excepInfo;
    UINT nArgErr;

    // ����OcrAuto
    HRESULT hr = InvokeSafely(pDispatch, dispid, &dispparams, &result, &excepInfo, &nArgErr);
    if (SUCCEEDED(hr)) {
        // ������
        if (result.vt == VT_BSTR) {
            wchar_t debugString[256];
            swprintf_s(debugString, L"ocr: %s", result.bstrVal);
            OutputDebugString(debugString);
            std::wstring wstr1(result.bstrVal, SysStringLen(result.bstrVal));
            return wstr1;
        }
        VariantClear(&result);
    }
    else {
        OutputDebugString(L"����OcrAutoʧ��\n");
    }

    // ����
    for (int i = 0; i < 5; ++i) {
        VariantClear(&varg[i]);
    }
    return L"";

}
bool ʶ����::��������()
{
    std::wstring �ַ� = ��ȡ�ַ�(����);
    if (�ַ�.find(L"����")!=std::wstring::npos || �ַ�.find(L"��") != std::wstring::npos || �ַ�.find(L"��") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::����װ������()
{
    std::wstring �ַ� = ��ȡ�ַ�(װ������);
    if (�ַ�.find(L"װ������") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::���Ҵ���()
{
    std::wstring �ַ� = ��ȡ�ַ�(����);
    if (�ַ�.find(L"����") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::����װ������()
{
    std::wstring �ַ� = ��ȡ�ַ�(װ������,0.1);
    if (�ַ�.find(L"����") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::�������()
{
    std::wstring �ַ� = ��ȡ�ַ�(���);
    if (�ַ�.find(L"���") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::����˲���ƶ�()
{
    std::wstring �ַ� = ��ȡ�ַ�(˲���ƶ�);
    if (�ַ�.find(L"˲���ƶ�") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::���ҹ���()
{
    std::wstring �ַ� = ��ȡ�ַ�(����);
    if (�ַ�.find(L"����") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::������������()
{
    std::wstring �ַ� = ��ȡ�ַ�(��������);
    if (�ַ�.find(L"��������") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::�����������δ���()
{
    std::wstring �ַ� = ��ȡ�ַ�(�������δ���);
    if (�ַ�.find(L"����") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::���ҽڵ�ģʽ()
{
    std::wstring �ַ� = ��ȡ�ַ�(�ڵ�ģʽ);
    if (�ַ�.find(L"�ڵ�ģʽ") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::���Ҹ���()
{
    std::wstring �ַ� = ��ȡ�ַ�(����);
    if (�ַ�.find(L"����") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::����С��ͼ_��ά����˹�Ǳ�()
{
    std::wstring �ַ� = ��ȡ�ַ�(С��ͼ_��ά����˹�Ǳ�);
    if (�ַ�.find(L"��ά����˹�Ǳ�") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::����С��ͼ_�ӻ�()
{
    std::wstring �ַ� = ��ȡ�ַ�(С��ͼ_�ӻ�);
    if (�ַ�.find(L"�ӻ�") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::���ұ���()
{
    std::wstring �ַ� = ��ȡ�ַ�(����);
    if (�ַ�.find(L"����") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::���ұ���������˵��()
{
    std::wstring �ַ� = ��ȡ�ַ�(����������˵��);
    if (�ַ�.find(L"������") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::������������()
{
    std::wstring �ַ� = ��ȡ�ַ�(��������);
    if (�ַ�.find(L"��������") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::���Ҽ��������Զ��ͷ�()
{
    std::wstring �ַ� = ��ȡ�ַ�(���������Զ��ͷ�);
    if (�ַ�.find(L"����") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::��������_���ļ����Զ�����()
{
    std::wstring �ַ� = ��ȡ�ַ�(����_���ļ����Զ�����);
    if (�ַ�.find(L"����") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::����������ʿ()
{
    std::wstring �ַ� = ��ȡ�ַ�(������ʿ);
    if (�ַ�.find(L"������ʿ") != std::wstring::npos) {
        return true;
    }
    return false;
}
int ʶ����::���ҿ����ҩƷ����()
{
    std::wstring �ַ� = ��ȡ�ַ�(�����ҩƷ����,1);
    try
    {
        int number = std::stoi(�ַ�); // ��wstringת��Ϊint
        return number;
    }
    catch (const std::exception&)
    {
        return 9999;
    }
    return 9999;
}
bool ʶ����::���Ҵ��ͼ_����()
{
    std::wstring �ַ� = ��ȡ�ַ�(���ͼ_����);
    if (�ַ�.find(L"����") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::�����ӻ�����()
{
    std::wstring �ַ� = ��ȡ�ַ�(�ӻ�����);
    if (�ַ�.find(L"�ӻ�����") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::���ҽ�����Ϸ()
{
    std::wstring �ַ� = ��ȡ�ַ�(������Ϸ);
    if (�ַ�.find(L"������Ϸ") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::����ְҵ()
{
    std::wstring �ַ� = ��ȡ�ַ�(ְҵ);
    if (�ַ�.find(L"ְҵ") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::���ҽ�������()
{
    std::wstring �ַ� = ��ȡ�ַ�(��������);
    if (�ַ�.find(L"����") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::�����Զ�������ҩ()
{
    std::wstring �ַ� = ��ȡ�ַ�(�Զ�������ҩ);
    if (�ַ�.find(L"����") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::����ǿ��ȷ�ϵ���()
{
    std::wstring �ַ� = ��ȡ�ַ�(ǿ��ȷ�ϵ���);
    if (�ַ�.find(L"ȷ�ϵ���") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::����ǿ�����ȫ�׶�()
{
    std::wstring �ַ� = ��ȡ�ַ�(ǿ�����ȫ�׶�);
    if (�ַ�.find(L"��ȫ�׶�") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::���Ҽ���������()
{
    std::wstring �ַ� = ��ȡ�ַ�(����������);
    if (�ַ�.find(L"����������") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::���Ҽ���_ʧ��()
{
    std::wstring �ַ� = ��ȡ�ַ�(����_ʧ��);
    if (�ַ�.find(L"ʧ��") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::���ҹ�����_���Ŀ���()
{
    std::wstring �ַ� = ��ȡ�ַ�(������_���Ŀ���);
    if (�ַ�.find(L"����") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::���ҹ�����_��׼�������()
{
    std::wstring �ַ� = ��ȡ�ַ�(������_��׼�������);
    if (�ַ�.find(L"����") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::���ҹ�����_��ʼ���Կ���()
{
    std::wstring �ַ� = ��ȡ�ַ�(������_��ʼ���Կ���);
    if (�ַ�.find(L"����") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool ʶ����::���ҹ�����_��ʴ����()
{
    std::wstring �ַ� = ��ȡ�ַ�(������_��ʴ����);
    if (�ַ�.find(L"��ʴ") != std::wstring::npos) {
        return true;
    }
    return false;
}
int ʶ����::���ҵȼ�()
{
    std::wstring �ַ� = ��ȡ�ַ�(�ȼ�, 1);
    try
    {
        int number = std::stoi(�ַ�); // ��wstringת��Ϊint
        return number;
    }
    catch (const std::exception&)
    {
        return 0;
    }
    return 0;
}
std::wstring ʶ����::��ȡ������Ʒ����()
{
    return ��ȡ�ַ�(������Ʒ����);
}
IDispatch* ʶ����::COM��ʼ��()
{ 
    pDispatch = NULL;
    std::wstring res = L"";
    OutputDebugStringA("start\n");
    hr = CoInitialize(NULL); // ��ʼ��COM��
    if (FAILED(hr)) {
        OutputDebugString(L"COM���ʼ��ʧ��");
        return pDispatch;
    }

    CLSID clsid;
    

    // ��ȡCLSID
    hr = CLSIDFromProgID(L"op.opsoft", &clsid);
    if (FAILED(hr)) {
        OutputDebugString(L"��ȡCLSIDʧ��");
        CoUninitialize();
        return pDispatch;
    }

    // ����COM����
    hr = CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void**)&pDispatch);
    if (FAILED(hr)) {
        OutputDebugString(L"����COM����ʧ��");
        CoUninitialize();
        return pDispatch;
    }

    // ��ȡOcrAuto��DISPID
    OLECHAR* methodName = L"OcrAuto";
    
    hr = pDispatch->GetIDsOfNames(IID_NULL, &methodName, 1, GetUserDefaultLCID(), &dispid);
    if (FAILED(hr)) {
        OutputDebugString(L"��ȡOcrAuto��DISPIDʧ��");
        pDispatch->Release();
        CoUninitialize();
        return pDispatch;
    }
    return pDispatch;
}
