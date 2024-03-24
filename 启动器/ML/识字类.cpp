#include "pch.h"
#include "识字类.h"

HRESULT InvokeSafely(IDispatch* pDispatch, DISPID dispid, DISPPARAMS* pDispParams, VARIANT* pResult, EXCEPINFO* pExcepInfo, unsigned int* puArgErr) {
    if (pDispatch == nullptr || pDispParams == nullptr || pResult == nullptr || pExcepInfo == nullptr || puArgErr == nullptr) {
        // 如果任何一个参数是空指针，返回错误码，例如 E_POINTER
        return -1;
    }
    __try {
        return pDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, pDispParams, pResult, pExcepInfo, puArgErr);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        // 处理异常，例如记录日志或返回特定的错误码
        return -1;
    }
}
HMODULE 识字类::LoadDll()
{
	HMODULE hModule = LoadLibraryA("op_x64.dll");
	if (hModule == NULL) {
		// 处理错误
		OutputDebugStringA(" failed load op_x64.dll:\n ");
	}/*
	libop opFunc = (libop)GetProcAddress(hModule, "libop");
	libop* op = opFunc();*/
	return hModule;
}


std::wstring 识字类::获取字符(识字坐标 坐标)
{

    // 准备调用OcrAuto
    DISPPARAMS dispparams;
    VARIANTARG varg[5];
    VariantInit(&varg[4]);
    varg[4].vt = VT_I4;
    varg[4].lVal = 坐标.x1;
    VariantInit(&varg[3]);
    varg[3].vt = VT_I4;
    varg[3].lVal = 坐标.y1;
    VariantInit(&varg[2]);
    varg[2].vt = VT_I4;
    varg[2].lVal = 坐标.x2;
    VariantInit(&varg[1]);
    varg[1].vt = VT_I4;
    varg[1].lVal = 坐标.y2;
    VariantInit(&varg[0]);
    varg[0].vt = VT_R8;
    varg[0].dblVal = 0.5;

    dispparams.rgvarg = varg;
    dispparams.cArgs = 5;
    dispparams.cNamedArgs = 0;

    VARIANT result;
    VariantInit(&result);
    EXCEPINFO excepInfo;
    UINT nArgErr;

    // 调用OcrAuto
    HRESULT hr = InvokeSafely(pDispatch, dispid, &dispparams, &result, &excepInfo, &nArgErr);
    if (SUCCEEDED(hr)) {
        // 输出结果
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
        OutputDebugString(L"调用OcrAuto失败\n");
    }

    // 清理
    for (int i = 0; i < 5; ++i) {
        VariantClear(&varg[i]);
    }
    return L"";

}
bool 识字类::查找跳过()
{
    std::wstring 字符 = 获取字符(跳过);
    if (字符.find(L"跳过")!=std::wstring::npos) {
        return true;
    }
    return false;
}
bool 识字类::查找装备坐骑()
{
    std::wstring 字符 = 获取字符(装备坐骑);
    if (字符.find(L"装备坐骑") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool 识字类::查找穿戴()
{
    std::wstring 字符 = 获取字符(穿戴);
    if (字符.find(L"穿戴") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool 识字类::查找装备穿戴()
{
    std::wstring 字符 = 获取字符(装备穿戴);
    if (字符.find(L"穿戴") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool 识字类::查找添加()
{
    std::wstring 字符 = 获取字符(添加);
    if (字符.find(L"添加") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool 识字类::查找瞬间移动()
{
    std::wstring 字符 = 获取字符(瞬间移动);
    if (字符.find(L"瞬间移动") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool 识字类::查找购买()
{
    std::wstring 字符 = 获取字符(购买);
    if (字符.find(L"购买") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool 识字类::查找请点击画面()
{
    std::wstring 字符 = 获取字符(请点击画面);
    if (字符.find(L"请点击画面") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool 识字类::查找武器外形穿戴()
{
    std::wstring 字符 = 获取字符(武器外形穿戴);
    if (字符.find(L"穿戴") != std::wstring::npos) {
        return true;
    }
    return false;
}
bool 识字类::查找节电模式()
{
    std::wstring 字符 = 获取字符(节电模式);
    if (字符.find(L"节电模式") != std::wstring::npos) {
        return true;
    }
    return false;
}
IDispatch* 识字类::COM初始化()
{ 
    pDispatch = NULL;
    std::wstring res = L"";
    OutputDebugStringA("start\n");
    hr = CoInitialize(NULL); // 初始化COM库
    if (FAILED(hr)) {
        OutputDebugString(L"COM库初始化失败");
        return pDispatch;
    }

    CLSID clsid;
    

    // 获取CLSID
    hr = CLSIDFromProgID(L"op.opsoft", &clsid);
    if (FAILED(hr)) {
        OutputDebugString(L"获取CLSID失败");
        CoUninitialize();
        return pDispatch;
    }

    // 创建COM对象
    hr = CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void**)&pDispatch);
    if (FAILED(hr)) {
        OutputDebugString(L"创建COM对象失败");
        CoUninitialize();
        return pDispatch;
    }

    // 获取OcrAuto的DISPID
    OLECHAR* methodName = L"OcrAuto";
    
    hr = pDispatch->GetIDsOfNames(IID_NULL, &methodName, 1, GetUserDefaultLCID(), &dispid);
    if (FAILED(hr)) {
        OutputDebugString(L"获取OcrAuto的DISPID失败");
        pDispatch->Release();
        CoUninitialize();
        return pDispatch;
    }
    return pDispatch;
}
