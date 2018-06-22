// ThreeOrderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MultimediaProject.h"
#include "ThreeOrderDlg.h"
#include "afxdialogex.h"


// CThreeOrderDlg �Ի���

IMPLEMENT_DYNAMIC(CThreeOrderDlg, CDialogEx)

CThreeOrderDlg::CThreeOrderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CThreeOrderDlg::IDD, pParent)
{
	EnableAutomation();
	m_edita1 = 0.75;
	m_edita2 = 0.75;
	m_edita3 = -0.5;
}

CThreeOrderDlg::~CThreeOrderDlg()
{
}

void CThreeOrderDlg::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CThreeOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TA1, m_edita1);
	DDX_Text(pDX, IDC_TA2, m_edita2);
	DDX_Text(pDX, IDC_TA3, m_edita3);
}


BEGIN_MESSAGE_MAP(CThreeOrderDlg, CDialogEx)
	ON_EN_CHANGE(IDC_TA1, &CThreeOrderDlg::OnEnChangea1)
	ON_EN_CHANGE(IDC_TA2, &CThreeOrderDlg::OnEnChangea2)
	ON_EN_CHANGE(IDC_TA3, &CThreeOrderDlg::OnEnChangea3)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CThreeOrderDlg, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_ICThreeOrderDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {C5E9313F-8FEA-4DCA-956E-809D8B3F7709}
static const IID IID_ICThreeOrderDlg =
{ 0xC5E9313F, 0x8FEA, 0x4DCA, { 0x95, 0x6E, 0x80, 0x9D, 0x8B, 0x3F, 0x77, 0x9 } };

BEGIN_INTERFACE_MAP(CThreeOrderDlg, CDialogEx)
	INTERFACE_PART(CThreeOrderDlg, IID_ICThreeOrderDlg, Dispatch)
END_INTERFACE_MAP()

// CThreeOrderDlg ��Ϣ�������
void CThreeOrderDlg::OnEnChangea1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}

void CThreeOrderDlg::OnEnChangea2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}

void CThreeOrderDlg::OnEnChangea3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}