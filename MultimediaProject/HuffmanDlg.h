#pragma once


// CHuffmanDlg �Ի���

class CHuffmanDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHuffmanDlg)

public:
	// �Ҷȼ���256��
	int nColorNum;

	// �Ҷ�ֵ���ָ���
	double *  dProba;

	// ���������
	CString	* m_strCode;

	CHuffmanDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHuffmanDlg();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_HUFFMAN };
	CListCtrl	m_lstTable;
	double	m_dEntropy;
	double	m_dCodLength;
	double	m_dRatio;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
