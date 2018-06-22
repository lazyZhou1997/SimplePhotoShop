#pragma once


// CYOneOrderDlg 对话框

class CYOneOrderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CYOneOrderDlg)

public:
	CYOneOrderDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CYOneOrderDlg();
	
	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_YOneOrder };
	double m_editay;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

public:
	afx_msg void OnEnChangeAy();
};
