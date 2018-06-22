#pragma once

#include "Histogram.h"
// CHistogramDrawDlg 对话框

class CHistogramDrawDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHistogramDrawDlg)

public:
	CHistogramDrawDlg(CWnd* pParent = NULL);   // 标准构造函数
	
	Histogram m_histogramDib;
	
	virtual ~CHistogramDrawDlg();

// 对话框数据
	enum { IDD = IDD_HistogramDraw };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};
