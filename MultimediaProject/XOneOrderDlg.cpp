// XOneOrderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MultimediaProject.h"
#include "XOneOrderDlg.h"
#include "afxdialogex.h"


// CXOneOrderDlg �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_ICXOneOrderDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {C5E9313F-8FEA-4DCA-956E-809D8B3F7709}
static const IID IID_ICXOneOrderDlg =
{ 0xC5E9313F, 0x8FEA, 0x4DCA, { 0x95, 0x6E, 0x80, 0x9D, 0x8B, 0x3F, 0x77, 0x9 } };

BEGIN_INTERFACE_MAP(CXOneOrderDlg, CDialogEx)
	INTERFACE_PART(CXOneOrderDlg, IID_ICXOneOrderDlg, Dispatch)
END_INTERFACE_MAP()

// CXOneOrderDlg ��Ϣ�������
void CXOneOrderDlg::OnEnChangeAx()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}

