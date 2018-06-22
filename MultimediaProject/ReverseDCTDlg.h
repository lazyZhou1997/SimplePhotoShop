#pragma once


// CReverseDCTDlg 对话框

class CReverseDCTDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReverseDCTDlg)

public:
	CReverseDCTDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReverseDCTDlg();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_RDCT };
	int m_ratio;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
