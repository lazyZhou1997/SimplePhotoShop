#pragma once


// DitherDlg �Ի���

class DitherDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DitherDlg)

public:
	DitherDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DitherDlg();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_DITHER };
	int m_Dn;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
