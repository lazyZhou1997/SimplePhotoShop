#pragma once


// CDCTDlg �Ի���

class CDCTDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDCTDlg)

public:
	CDCTDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDCTDlg();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_DCT };
	int m_width;
	int m_height;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
