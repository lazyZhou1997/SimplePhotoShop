#pragma once


// DitherDlg 对话框

class DitherDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DitherDlg)

public:
	DitherDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DitherDlg();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_DITHER };
	int m_Dn;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
