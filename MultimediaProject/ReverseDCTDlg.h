#pragma once


// CReverseDCTDlg �Ի���

class CReverseDCTDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReverseDCTDlg)

public:
	CReverseDCTDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReverseDCTDlg();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_RDCT };
	int m_ratio;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
