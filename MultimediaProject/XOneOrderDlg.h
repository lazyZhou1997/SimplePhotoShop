#pragma once


// CXOneOrderDlg 对话框

class CXOneOrderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CXOneOrderDlg)

public:
	CXOneOrderDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CXOneOrderDlg();
	
	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_XOneOrder };
	double m_editax;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnEnChangeAx();
};
