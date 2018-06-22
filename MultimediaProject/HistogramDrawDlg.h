#pragma once

#include "Histogram.h"
// CHistogramDrawDlg �Ի���

class CHistogramDrawDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHistogramDrawDlg)

public:
	CHistogramDrawDlg(CWnd* pParent = NULL);   // ��׼���캯��
	
	Histogram m_histogramDib;
	
	virtual ~CHistogramDrawDlg();

// �Ի�������
	enum { IDD = IDD_HistogramDraw };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};
