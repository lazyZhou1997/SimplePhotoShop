// SingleThresholdDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MultimediaProject.h"
#include "SingleThresholdDlg.h"
#include "afxdialogex.h"


// CSingleThresholdDlg �Ի���

IMPLEMENT_DYNAMIC(CSingleThresholdDlg, CDialogEx)

CSingleThresholdDlg::CSingleThresholdDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSingleThresholdDlg::IDD, pParent)
{

	EnableAutomation();
	m_threshold = 100;

}

CSingleThresholdDlg::~CSingleThresholdDlg()
{
}

void CSingleThresholdDlg::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CSingleThresholdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_threshold);
}


BEGIN_MESSAGE_MAP(CSingleThresholdDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CSingleThresholdDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CSingleThresholdDlg, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_ISingleThresholdDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {C5E9313F-8FEA-4DCA-956E-809D8B3F7709}
static const IID IID_ISingleThresholdDlg =
{ 0xC5E9313F, 0x8FEA, 0x4DCA, { 0x95, 0x6E, 0x80, 0x9D, 0x8B, 0x3F, 0x77, 0x9 } };

BEGIN_INTERFACE_MAP(CSingleThresholdDlg, CDialogEx)
	INTERFACE_PART(CSingleThresholdDlg, IID_ISingleThresholdDlg, Dispatch)
END_INTERFACE_MAP()


// CSingleThresholdDlg ��Ϣ�������


void CSingleThresholdDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
