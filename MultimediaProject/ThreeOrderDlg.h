#pragma once


// CThreeOrderDlg �Ի���

class CThreeOrderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CThreeOrderDlg)

public:
	CThreeOrderDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CThreeOrderDlg();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_ThreeOrder };
	double m_edita1;
	double m_edita2;
	double m_edita3;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

public:
	afx_msg void OnEnChangea1();
	afx_msg void OnEnChangea2();
	afx_msg void OnEnChangea3();
};
