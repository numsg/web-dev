// TestOCX.cpp : CTestOCXApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "TestOCX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CTestOCXApp theApp;

const GUID CDECL _tlid = { 0x3F91FFE5, 0xC6D9, 0x4CB6, { 0xBE, 0x23, 0x38, 0xE3, 0x72, 0x10, 0x6A, 0x16 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CTestOCXApp::InitInstance - DLL 初始化

BOOL CTestOCXApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: 在此添加您自己的模块初始化代码。
	}

	return bInit;
}



// CTestOCXApp::ExitInstance - DLL 终止

int CTestOCXApp::ExitInstance()
{
	// TODO: 在此添加您自己的模块终止代码。

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
