// ReverseDCTDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MultimediaProject.h"
#include "ReverseDCTDlg.h"
#include "afxdialogex.h"


// CReverseDCTDlg 对话框

IMPLEMENT_DYNAMIC(CReverseDCTDlg, CDialogEx)

CReverseDCTDlg::CReverseDCTDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReverseDCTDlg::IDD, pParent)
{

	EnableAutomation();
	m_ratio = 50;

}

CReverseDCTDlg::~CReverseDCTDlg()
{
}

void CReverseDCTDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CReverseDCTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ratio);
}


BEGIN_MESSAGE_MAP(CReverseDCTDlg, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CReverseDCTDlg, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IReverseDCTDlg 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {8726969C-8C3F-4DA6-993A-9230F7A4D258}
static const IID IID_IReverseDCTDlg =
{ 0x8726969C, 0x8C3F, 0x4DA6, { 0x99, 0x3A, 0x92, 0x30, 0xF7, 0xA4, 0xD2, 0x58 } };

BEGIN_INTERFACE_MAP(CReverseDCTDlg, CDialogEx)
	INTERFACE_PART(CReverseDCTDlg, IID_IReverseDCTDlg, Dispatch)
END_INTERFACE_MAP()


// CReverseDCTDlg 消息处理程序
