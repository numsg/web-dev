// TestOCXCtrl.cpp : CTestOCXCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "TestOCX.h"
#include "TestOCXCtrl.h"
#include "TestOCXPropPage.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CTestOCXCtrl, COleControl)

// 消息映射

BEGIN_MESSAGE_MAP(CTestOCXCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

// 调度映射

BEGIN_DISPATCH_MAP(CTestOCXCtrl, COleControl)
	DISP_FUNCTION_ID(CTestOCXCtrl, "test", dispidtest, test, VT_I4, VTS_I4 VTS_I4)
END_DISPATCH_MAP()

// 事件映射

BEGIN_EVENT_MAP(CTestOCXCtrl, COleControl)
END_EVENT_MAP()

// 属性页

// TODO: 按需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CTestOCXCtrl, 1)
	PROPPAGEID(CTestOCXPropPage::guid)
END_PROPPAGEIDS(CTestOCXCtrl)

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CTestOCXCtrl, "TESTOCX.TestOCXCtrl.1",
	0x64947e15, 0x852e, 0x496e, 0xb3, 0xb1, 0xac, 0xcf, 0x57, 0x42, 0xbd, 0x4c)

// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CTestOCXCtrl, _tlid, _wVerMajor, _wVerMinor)

// 接口 ID

const IID IID_DTestOCX = { 0x1DB9F27, 0x7338, 0x43E5, { 0xA9, 0xFD, 0xC2, 0x37, 0x3E, 0x9F, 0xF7, 0x44 } };
const IID IID_DTestOCXEvents = { 0xE0DD2328, 0xEA9, 0x41CF, { 0x85, 0x8D, 0x94, 0x73, 0x3, 0x9C, 0x33, 0xB3 } };

// 控件类型信息

static const DWORD _dwTestOCXOleMisc =
	OLEMISC_INVISIBLEATRUNTIME |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CTestOCXCtrl, IDS_TESTOCX, _dwTestOCXOleMisc)

// CTestOCXCtrl::CTestOCXCtrlFactory::UpdateRegistry -
// 添加或移除 CTestOCXCtrl 的系统注册表项

BOOL CTestOCXCtrl::CTestOCXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: 验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_TESTOCX,
			IDB_TESTOCX,
			afxRegApartmentThreading,
			_dwTestOCXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


// CTestOCXCtrl::CTestOCXCtrl - 构造函数

CTestOCXCtrl::CTestOCXCtrl()
{
	InitializeIIDs(&IID_DTestOCX, &IID_DTestOCXEvents);
	// TODO: 在此初始化控件的实例数据。
}



// CTestOCXCtrl::~CTestOCXCtrl - 析构函数

CTestOCXCtrl::~CTestOCXCtrl()
{
	// TODO: 在此清理控件的实例数据。
}


BOOL CTestOCXCtrl::IsInvokeAllowed (DISPID)
{
	return true;
}

// CTestOCXCtrl::OnDraw - 绘图函数

void CTestOCXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: 用您自己的绘图代码替换下面的代码。
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}

// CTestOCXCtrl::DoPropExchange - 持久性支持

void CTestOCXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}


// CTestOCXCtrl::OnResetState - 将控件重置为默认状态

void CTestOCXCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO: 在此重置任意其他控件状态。
}


// CTestOCXCtrl 消息处理程序


LONG CTestOCXCtrl::test(LONG a, LONG b)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return a + b;
}

