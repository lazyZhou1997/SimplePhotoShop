#pragma once


// CDCTDlg 对话框

class CDCTDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDCTDlg)

public:
	CDCTDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDCTDlg();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_DCT };
	int m_width;
	int m_height;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
