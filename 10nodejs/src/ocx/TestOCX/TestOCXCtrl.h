#pragma once

// TestOCXCtrl.h : CTestOCXCtrl ActiveX 控件类的声明。


// CTestOCXCtrl : 有关实现的信息，请参阅 TestOCXCtrl.cpp。

class CTestOCXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CTestOCXCtrl)

// 构造函数
public:
	CTestOCXCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual BOOL CTestOCXCtrl::IsInvokeAllowed (DISPID);

// 实现
protected:
	~CTestOCXCtrl();

	DECLARE_OLECREATE_EX(CTestOCXCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CTestOCXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CTestOCXCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CTestOCXCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
		dispidtest = 1L
	};
protected:
	LONG test(LONG a, LONG b);
};

