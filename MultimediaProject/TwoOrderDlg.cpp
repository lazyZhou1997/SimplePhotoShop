// TwoOrderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MultimediaProject.h"
#include "TwoOrderDlg.h"
#include "afxdialogex.h"


// CTwoOrderDlg �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_ICTwoOrderDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {C5E9313F-8FEA-4DCA-956E-809D8B3F7709}
static const IID IID_ICTwoOrderDlg =
{ 0xC5E9313F, 0x8FEA, 0x4DCA, { 0x95, 0x6E, 0x80, 0x9D, 0x8B, 0x3F, 0x77, 0x9 } };

BEGIN_INTERFACE_MAP(CTwoOrderDlg, CDialogEx)
	INTERFACE_PART(CTwoOrderDlg, IID_ICTwoOrderDlg, Dispatch)
END_INTERFACE_MAP()

// CXOneOrderDlg ��Ϣ�������
void CTwoOrderDlg::OnEnChangeA1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}

void CTwoOrderDlg::OnEnChangeA2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}
