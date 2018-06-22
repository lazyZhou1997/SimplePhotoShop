#pragma once


// CSingleThresholdDlg 对话框

class CSingleThresholdDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSingleThresholdDlg)

public:
	CSingleThresholdDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSingleThresholdDlg();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_SINGLETHRESHOLD };
	int m_threshold;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
};
