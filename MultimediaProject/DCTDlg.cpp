// DCTDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MultimediaProject.h"
#include "DCTDlg.h"
#include "afxdialogex.h"


// CDCTDlg �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_IDCTDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {FDCA2365-9D7C-4563-B916-A35DA980DC2E}
static const IID IID_IDCTDlg =
{ 0xFDCA2365, 0x9D7C, 0x4563, { 0xB9, 0x16, 0xA3, 0x5D, 0xA9, 0x80, 0xDC, 0x2E } };

BEGIN_INTERFACE_MAP(CDCTDlg, CDialogEx)
	INTERFACE_PART(CDCTDlg, IID_IDCTDlg, Dispatch)
END_INTERFACE_MAP()


// CDCTDlg ��Ϣ�������
