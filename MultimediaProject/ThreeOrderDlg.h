#pragma once


// CThreeOrderDlg 对话框

class CThreeOrderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CThreeOrderDlg)

public:
	CThreeOrderDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CThreeOrderDlg();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_ThreeOrder };
	double m_edita1;
	double m_edita2;
	double m_edita3;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

public:
	afx_msg void OnEnChangea1();
	afx_msg void OnEnChangea2();
	afx_msg void OnEnChangea3();
};
