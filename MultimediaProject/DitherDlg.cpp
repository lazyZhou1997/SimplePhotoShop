// DitherDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MultimediaProject.h"
#include "DitherDlg.h"
#include "afxdialogex.h"


// DitherDlg �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_IDitherDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {E7618589-E3D6-4E1B-8A70-2511D4558287}
static const IID IID_IDitherDlg =
{ 0xE7618589, 0xE3D6, 0x4E1B, { 0x8A, 0x70, 0x25, 0x11, 0xD4, 0x55, 0x82, 0x87 } };

BEGIN_INTERFACE_MAP(DitherDlg, CDialogEx)
	INTERFACE_PART(DitherDlg, IID_IDitherDlg, Dispatch)
END_INTERFACE_MAP()


// DitherDlg ��Ϣ�������
