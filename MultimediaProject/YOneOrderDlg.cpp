// YOneOrderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MultimediaProject.h"
#include "YOneOrderDlg.h"
#include "afxdialogex.h"


// CYOneOrderDlg �Ի���

IMPLEMENT_DYNAMIC(CYOneOrderDlg, CDialogEx)

CYOneOrderDlg::CYOneOrderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CYOneOrderDlg::IDD, pParent)
{
	EnableAutomation();
	m_editay = 0.97;
}

CYOneOrderDlg::~CYOneOrderDlg()
{
}

void CYOneOrderDlg::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CYOneOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Ay, m_editay);
}


BEGIN_MESSAGE_MAP(CYOneOrderDlg, CDialogEx)
	ON_EN_CHANGE(IDC_Ay, &CYOneOrderDlg::OnEnChangeAy)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CYOneOrderDlg, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_ICYOneOrderDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {C5E9313F-8FEA-4DCA-956E-809D8B3F7709}
static const IID IID_ICYOneOrderDlg =
{ 0xC5E9313F, 0x8FEA, 0x4DCA, { 0x95, 0x6E, 0x80, 0x9D, 0x8B, 0x3F, 0x77, 0x9 } };

BEGIN_INTERFACE_MAP(CYOneOrderDlg, CDialogEx)
	INTERFACE_PART(CYOneOrderDlg, IID_ICYOneOrderDlg, Dispatch)
END_INTERFACE_MAP()

// CXOneOrderDlg ��Ϣ�������
void CYOneOrderDlg::OnEnChangeAy()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}

