#pragma once


// CYOneOrderDlg �Ի���

class CYOneOrderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CYOneOrderDlg)

public:
	CYOneOrderDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CYOneOrderDlg();
	
	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_YOneOrder };
	double m_editay;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

public:
	afx_msg void OnEnChangeAy();
};
