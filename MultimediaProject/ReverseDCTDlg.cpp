// ReverseDCTDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MultimediaProject.h"
#include "ReverseDCTDlg.h"
#include "afxdialogex.h"


// CReverseDCTDlg �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_IReverseDCTDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {8726969C-8C3F-4DA6-993A-9230F7A4D258}
static const IID IID_IReverseDCTDlg =
{ 0x8726969C, 0x8C3F, 0x4DA6, { 0x99, 0x3A, 0x92, 0x30, 0xF7, 0xA4, 0xD2, 0x58 } };

BEGIN_INTERFACE_MAP(CReverseDCTDlg, CDialogEx)
	INTERFACE_PART(CReverseDCTDlg, IID_IReverseDCTDlg, Dispatch)
END_INTERFACE_MAP()


// CReverseDCTDlg ��Ϣ�������
