// HistogramDrawDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MultimediaProject.h"
#include "HistogramDrawDlg.h"
#include "ImgDib.h"
#include "Histogram.h"
#include "afxdialogex.h"


// CHistogramDrawDlg 对话框

IMPLEMENT_DYNAMIC(CHistogramDrawDlg, CDialogEx)

CHistogramDrawDlg::CHistogramDrawDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHistogramDrawDlg::IDD, pParent)
{

}

CHistogramDrawDlg::~CHistogramDrawDlg()
{
}

void CHistogramDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHistogramDrawDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CHistogramDrawDlg 消息处理程序
BOOL CHistogramDrawDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//将静态框1移至rect指定位置，用来画直方图
	CRect rect;
	rect=CRect(25,51,279,151);
	GetDlgItem(IDC_STATIC_HistRect)->MoveWindow(&rect);

	//将确定按钮移至指定位置
	rect=CRect(221,210,277,234);
	GetDlgItem(IDOK)->MoveWindow(&rect);

	// 如果是灰度图像，则调用灰度直方图统计函数
	if(m_histogramDib.m_nBitCount==8)
    	m_histogramDib.computeHistGray();
	else//彩色图像则统计亮度直方图
		m_histogramDib.computeHistBrightness();
	return TRUE;  
}

void CHistogramDrawDlg::OnPaint() 
{
	//设备环境对象
	CPaintDC dc(this); // device context for painting

	//彩色和灰度图像有效
	if(m_histogramDib.m_nBitCount != 8 && m_histogramDib.m_nBitCount != 24) 
		return ;
	
	if(m_histogramDib.m_nBitCount == 8){
	//获取直方图绘制静态框的矩形区域
 	CRect clientRect;  
	GetDlgItem(IDC_STATIC_HistRect)->GetWindowRect(&clientRect);
	ScreenToClient(&clientRect);

	BeginWaitCursor();	    // Draw Back Ground
	//画背景
	dc.SelectStockObject(NULL_BRUSH);
	dc.Rectangle(clientRect.left-1, clientRect.top,
                          clientRect.right+3, clientRect.bottom+1);
	
	//画直方图灰度频率与直方图绘制矩形区域比例关系，画直方图
	unsigned int max=0;;
	for(int i=0;i<256;i++){
		if(m_histogramDib.m_histArray[i]>max)
			max=m_histogramDib.m_histArray[i];
	}
	DWORD bufTemp[256];
	double x=clientRect.Height();
	for(int i=0;i<256;i++){
		bufTemp[i]=(unsigned long)((float)m_histogramDib.m_histArray[i]*x/max);
	}
	for(int i=clientRect.left;i<=clientRect.right;i++){
		dc.MoveTo(i,clientRect.bottom);
		dc.LineTo(i,clientRect.bottom-bufTemp[i-clientRect.left]);
	}   

 	EndWaitCursor();
	}

	if(m_histogramDib.m_nBitCount == 24){
	//获取直方图绘制静态框的矩形区域
 	CRect clientRect;  
	GetDlgItem(IDC_STATIC_HistRect)->GetWindowRect(&clientRect);
	ScreenToClient(&clientRect);

	BeginWaitCursor();	    // Draw Back Ground
	//画背景
	dc.SelectStockObject(NULL_BRUSH);
	dc.Rectangle(clientRect.left-1, clientRect.top,
                          clientRect.right+3, clientRect.bottom+1);
	
	//画直方图灰度频率与直方图绘制矩形区域比例关系，画直方图
	unsigned int max=0;;
	for(int i=0;i<256;i++){
		if(m_histogramDib.m_histArrayY[i]>max)
			max=m_histogramDib.m_histArrayY[i];
	}
	DWORD bufTemp[256];
	double x=clientRect.Height();
	for(int i=0;i<256;i++){
		bufTemp[i]=(unsigned long)((float)m_histogramDib.m_histArrayY[i]*x/max);
	}
	for(int i=clientRect.left;i<=clientRect.right;i++){
		dc.MoveTo(i,clientRect.bottom);
		dc.LineTo(i,clientRect.bottom-bufTemp[i-clientRect.left]);
	}   

 	EndWaitCursor();
	}
}

void CHistogramDrawDlg::OnSize(UINT nType, int cx, int cy) 
{
	//该函数在创建对话框时调用，确定直方图对话框的大小及客户区中的位置

	CDialog::OnSize(nType, cx, cy);
	CRect rect;
	rect=CRect(405,261,717,545);
	MoveWindow(&rect);
}
