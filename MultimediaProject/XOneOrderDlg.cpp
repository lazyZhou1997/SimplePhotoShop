// XOneOrderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MultimediaProject.h"
#include "XOneOrderDlg.h"
#include "afxdialogex.h"


// CXOneOrderDlg 对话框

IMPLEMENT_DYNAMIC(CXOneOrderDlg, CDialogEx)

CXOneOrderDlg::CXOneOrderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CXOneOrderDlg::IDD, pParent)
{
	EnableAutomation();
	m_editax = 0.97;
}

CXOneOrderDlg::~CXOneOrderDlg()
{
}

void CXOneOrderDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CXOneOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Ax, m_editax);
}


BEGIN_MESSAGE_MAP(CXOneOrderDlg, CDialogEx)
	ON_EN_CHANGE(IDC_Ax, &CXOneOrderDlg::OnEnChangeAx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CXOneOrderDlg, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_ICXOneOrderDlg 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {C5E9313F-8FEA-4DCA-956E-809D8B3F7709}
static const IID IID_ICXOneOrderDlg =
{ 0xC5E9313F, 0x8FEA, 0x4DCA, { 0x95, 0x6E, 0x80, 0x9D, 0x8B, 0x3F, 0x77, 0x9 } };

BEGIN_INTERFACE_MAP(CXOneOrderDlg, CDialogEx)
	INTERFACE_PART(CXOneOrderDlg, IID_ICXOneOrderDlg, Dispatch)
END_INTERFACE_MAP()

// CXOneOrderDlg 消息处理程序
void CXOneOrderDlg::OnEnChangeAx()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
}

