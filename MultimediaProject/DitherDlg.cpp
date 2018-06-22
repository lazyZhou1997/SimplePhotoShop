// DitherDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MultimediaProject.h"
#include "DitherDlg.h"
#include "afxdialogex.h"


// DitherDlg 对话框

IMPLEMENT_DYNAMIC(DitherDlg, CDialogEx)

DitherDlg::DitherDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(DitherDlg::IDD, pParent)
{

	EnableAutomation();
	m_Dn = 2;

}

DitherDlg::~DitherDlg()
{
}

void DitherDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void DitherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Dn);
}


BEGIN_MESSAGE_MAP(DitherDlg, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(DitherDlg, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IDitherDlg 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {E7618589-E3D6-4E1B-8A70-2511D4558287}
static const IID IID_IDitherDlg =
{ 0xE7618589, 0xE3D6, 0x4E1B, { 0x8A, 0x70, 0x25, 0x11, 0xD4, 0x55, 0x82, 0x87 } };

BEGIN_INTERFACE_MAP(DitherDlg, CDialogEx)
	INTERFACE_PART(DitherDlg, IID_IDitherDlg, Dispatch)
END_INTERFACE_MAP()


// DitherDlg 消息处理程序
