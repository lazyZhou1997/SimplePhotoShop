#pragma once


// CSingleThresholdDlg �Ի���

class CSingleThresholdDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSingleThresholdDlg)

public:
	CSingleThresholdDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSingleThresholdDlg();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_SINGLETHRESHOLD };
	int m_threshold;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
};
