// HistogramDrawDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MultimediaProject.h"
#include "HistogramDrawDlg.h"
#include "ImgDib.h"
#include "Histogram.h"
#include "afxdialogex.h"


// CHistogramDrawDlg �Ի���

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


// CHistogramDrawDlg ��Ϣ�������
BOOL CHistogramDrawDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//����̬��1����rectָ��λ�ã�������ֱ��ͼ
	CRect rect;
	rect=CRect(25,51,279,151);
	GetDlgItem(IDC_STATIC_HistRect)->MoveWindow(&rect);

	//��ȷ����ť����ָ��λ��
	rect=CRect(221,210,277,234);
	GetDlgItem(IDOK)->MoveWindow(&rect);

	// ����ǻҶ�ͼ������ûҶ�ֱ��ͼͳ�ƺ���
	if(m_histogramDib.m_nBitCount==8)
    	m_histogramDib.computeHistGray();
	else//��ɫͼ����ͳ������ֱ��ͼ
		m_histogramDib.computeHistBrightness();
	return TRUE;  
}

void CHistogramDrawDlg::OnPaint() 
{
	//�豸��������
	CPaintDC dc(this); // device context for painting

	//��ɫ�ͻҶ�ͼ����Ч
	if(m_histogramDib.m_nBitCount != 8 && m_histogramDib.m_nBitCount != 24) 
		return ;
	
	if(m_histogramDib.m_nBitCount == 8){
	//��ȡֱ��ͼ���ƾ�̬��ľ�������
 	CRect clientRect;  
	GetDlgItem(IDC_STATIC_HistRect)->GetWindowRect(&clientRect);
	ScreenToClient(&clientRect);

	BeginWaitCursor();	    // Draw Back Ground
	//������
	dc.SelectStockObject(NULL_BRUSH);
	dc.Rectangle(clientRect.left-1, clientRect.top,
                          clientRect.right+3, clientRect.bottom+1);
	
	//��ֱ��ͼ�Ҷ�Ƶ����ֱ��ͼ���ƾ������������ϵ����ֱ��ͼ
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
	//��ȡֱ��ͼ���ƾ�̬��ľ�������
 	CRect clientRect;  
	GetDlgItem(IDC_STATIC_HistRect)->GetWindowRect(&clientRect);
	ScreenToClient(&clientRect);

	BeginWaitCursor();	    // Draw Back Ground
	//������
	dc.SelectStockObject(NULL_BRUSH);
	dc.Rectangle(clientRect.left-1, clientRect.top,
                          clientRect.right+3, clientRect.bottom+1);
	
	//��ֱ��ͼ�Ҷ�Ƶ����ֱ��ͼ���ƾ������������ϵ����ֱ��ͼ
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
	//�ú����ڴ����Ի���ʱ���ã�ȷ��ֱ��ͼ�Ի���Ĵ�С���ͻ����е�λ��

	CDialog::OnSize(nType, cx, cy);
	CRect rect;
	rect=CRect(405,261,717,545);
	MoveWindow(&rect);
}
