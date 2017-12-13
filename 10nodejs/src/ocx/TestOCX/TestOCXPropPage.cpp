// TestOCXPropPage.cpp : CTestOCXPropPage 属性页类的实现。

#include "stdafx.h"
#include "TestOCX.h"
#include "TestOCXPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CTestOCXPropPage, COlePropertyPage)

// 消息映射

BEGIN_MESSAGE_MAP(CTestOCXPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CTestOCXPropPage, "TESTOCX.TestOCXPropPage.1",
	0x1f087bbc, 0x7d7b, 0x455f, 0x9f, 0x84, 0x6e, 0x4d, 0x7d, 0xad, 0x75, 0x6)

// CTestOCXPropPage::CTestOCXPropPageFactory::UpdateRegistry -
// 添加或移除 CTestOCXPropPage 的系统注册表项

BOOL CTestOCXPropPage::CTestOCXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_TESTOCX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

// CTestOCXPropPage::CTestOCXPropPage - 构造函数

CTestOCXPropPage::CTestOCXPropPage() :
	COlePropertyPage(IDD, IDS_TESTOCX_PPG_CAPTION)
{
}

// CTestOCXPropPage::DoDataExchange - 在页和属性间移动数据

void CTestOCXPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CTestOCXPropPage 消息处理程序
