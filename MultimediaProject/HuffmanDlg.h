#pragma once


// CHuffmanDlg 对话框

class CHuffmanDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHuffmanDlg)

public:
	// 灰度级（256）
	int nColorNum;

	// 灰度值出现概率
	double *  dProba;

	// 哈夫曼码表
	CString	* m_strCode;

	CHuffmanDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHuffmanDlg();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_HUFFMAN };
	CListCtrl	m_lstTable;
	double	m_dEntropy;
	double	m_dCodLength;
	double	m_dRatio;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
