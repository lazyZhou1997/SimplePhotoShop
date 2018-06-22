// DCTDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MultimediaProject.h"
#include "DCTDlg.h"
#include "afxdialogex.h"


// CDCTDlg 对话框

IMPLEMENT_DYNAMIC(CDCTDlg, CDialogEx)

CDCTDlg::CDCTDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDCTDlg::IDD, pParent)
{

	EnableAutomation();
	m_width = 2;
	m_height = 2;

}

CDCTDlg::~CDCTDlg()
{
}

void CDCTDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CDCTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_width);
	DDX_Text(pDX, IDC_EDIT2, m_height);
}


BEGIN_MESSAGE_MAP(CDCTDlg, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDCTDlg, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IDCTDlg 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {FDCA2365-9D7C-4563-B916-A35DA980DC2E}
static const IID IID_IDCTDlg =
{ 0xFDCA2365, 0x9D7C, 0x4563, { 0xB9, 0x16, 0xA3, 0x5D, 0xA9, 0x80, 0xDC, 0x2E } };

BEGIN_INTERFACE_MAP(CDCTDlg, CDialogEx)
	INTERFACE_PART(CDCTDlg, IID_IDCTDlg, Dispatch)
END_INTERFACE_MAP()


// CDCTDlg 消息处理程序
