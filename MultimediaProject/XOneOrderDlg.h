#pragma once


// CXOneOrderDlg �Ի���

class CXOneOrderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CXOneOrderDlg)

public:
	CXOneOrderDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CXOneOrderDlg();
	
	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_XOneOrder };
	double m_editax;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnEnChangeAx();
};
