#pragma once


// CTwoOrderDlg �Ի���

class CTwoOrderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTwoOrderDlg)

public:
	CTwoOrderDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTwoOrderDlg();
	
	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_TwoOrder };
	double m_editA1;
	double m_editA2;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnEnChangeA1();
	afx_msg void OnEnChangeA2();
};
