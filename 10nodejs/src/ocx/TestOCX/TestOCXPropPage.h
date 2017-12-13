#pragma once

// TestOCXPropPage.h : CTestOCXPropPage 属性页类的声明。


// CTestOCXPropPage : 有关实现的信息，请参阅 TestOCXPropPage.cpp。

class CTestOCXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CTestOCXPropPage)
	DECLARE_OLECREATE_EX(CTestOCXPropPage)

// 构造函数
public:
	CTestOCXPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_TESTOCX };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

