// TwoOrderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MultimediaProject.h"
#include "TwoOrderDlg.h"
#include "afxdialogex.h"


// CTwoOrderDlg 对话框

IMPLEMENT_DYNAMIC(CTwoOrderDlg, CDialogEx)

CTwoOrderDlg::CTwoOrderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTwoOrderDlg::IDD, pParent)
{
	EnableAutomation();
	m_editA1 = 0.5;
	m_editA2 = 0.5;
}

CTwoOrderDlg::~CTwoOrderDlg()
{
}

void CTwoOrderDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CTwoOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_A1, m_editA1);
	DDX_Text(pDX, IDC_A2, m_editA2);
}


BEGIN_MESSAGE_MAP(CTwoOrderDlg, CDialogEx)
	ON_EN_CHANGE(IDC_A1, &CTwoOrderDlg::OnEnChangeA1)
	ON_EN_CHANGE(IDC_A2, &CTwoOrderDlg::OnEnChangeA2)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CTwoOrderDlg, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_ICTwoOrderDlg 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {C5E9313F-8FEA-4DCA-956E-809D8B3F7709}
static const IID IID_ICTwoOrderDlg =
{ 0xC5E9313F, 0x8FEA, 0x4DCA, { 0x95, 0x6E, 0x80, 0x9D, 0x8B, 0x3F, 0x77, 0x9 } };

BEGIN_INTERFACE_MAP(CTwoOrderDlg, CDialogEx)
	INTERFACE_PART(CTwoOrderDlg, IID_ICTwoOrderDlg, Dispatch)
END_INTERFACE_MAP()

// CXOneOrderDlg 消息处理程序
void CTwoOrderDlg::OnEnChangeA1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
}

void CTwoOrderDlg::OnEnChangeA2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
}
