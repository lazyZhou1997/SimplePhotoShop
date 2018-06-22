// MultimediaProjectView.cpp : CMultimediaProjectView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MultimediaProject.h"
#endif

#include "MultimediaProjectDoc.h"
#include "MultimediaProjectView.h"
#include "MainFrm.h"
#include "GrayTrans.h"
#include "Histogram.h"
#include "HistogramDrawDlg.h"
#include "XOneOrderDlg.h"
#include "YOneOrderDlg.h"
#include "TwoOrderDlg.h"
#include "ThreeOrderDlg.h"
#include "LosslessPredictiveCoding.h"
#include "SingleThresholdDlg.h"
#include "BinaryImg.h"
#include "DitherDlg.h"
#include "DCTDlg.h"
#include "DCTTransform.h"
#include "ReverseDCTDlg.h"
#include "HuffmanCoding.h"
#include "HuffmanDlg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMultimediaProjectView

IMPLEMENT_DYNCREATE(CMultimediaProjectView, CView)

BEGIN_MESSAGE_MAP(CMultimediaProjectView, CView)
		// ��׼��ӡ����
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMultimediaProjectView::OnFilePrintPreview)
		ON_WM_CONTEXTMENU()
		ON_WM_RBUTTONUP()
		ON_COMMAND(ID_32773, &CMultimediaProjectView::OnSingleThreshold)
		ON_COMMAND(ID_32774, &CMultimediaProjectView::OnDither)
		ON_COMMAND(ID_32775, &CMultimediaProjectView::OnOrderedDither)
		ON_COMMAND(ID_32783, &CMultimediaProjectView::UniformQuanlizationCR1) //CRΪ1�ľ�������
		ON_COMMAND(ID_32784, &CMultimediaProjectView::UniformQuanlizationCR2) //CRΪ2�ľ�������
		ON_COMMAND(ID_32785, &CMultimediaProjectView::UniformQuanlizationCR3) //CRΪ3�ľ�������
		ON_COMMAND(ID_32786, &CMultimediaProjectView::UniformQuanlizationCR4) //CRΪ4�ľ�������
		ON_COMMAND(ID_32787, &CMultimediaProjectView::IGSUniformQuanlization) //CRΪ2�Ľ���IGS�ľ�������
		ON_COMMAND(ID_32780, &CMultimediaProjectView::ShowDCTTransform) //����DCT�仯
		ON_COMMAND(ID_32781, &CMultimediaProjectView::ShowInverseDCTTransform) //���з�DCT�仯
		ON_COMMAND(ID_32788, &CMultimediaProjectView::OnRGBToHSI)
		ON_COMMAND(ID_32789, &CMultimediaProjectView::OnRGBToYCbCr)
		ON_COMMAND(ID_32777, &CMultimediaProjectView::OnHistogram)
		ON_COMMAND(ID_32793, &CMultimediaProjectView::OnxOneOrder)
		ON_COMMAND(ID_32795, &CMultimediaProjectView::OnyOneOrder)
		ON_COMMAND(ID_32791, &CMultimediaProjectView::OntwoOrder)
		ON_COMMAND(ID_32792, &CMultimediaProjectView::OnthreeOrder)
		ON_COMMAND(ID_32796, &CMultimediaProjectView::OnHistogramDraw)
		ON_COMMAND(ID_32797, &CMultimediaProjectView::OnHuffman)
END_MESSAGE_MAP()

// CMultimediaProjectView ����/����

CMultimediaProjectView::CMultimediaProjectView()
{
	// TODO:  �ڴ˴���ӹ������
}

CMultimediaProjectView::~CMultimediaProjectView()
{
}

BOOL CMultimediaProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMultimediaProjectView ����

void CMultimediaProjectView::OnDraw(CDC* pDC)
{
	CMultimediaProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���

	//����myDib��ָ��
	ImgDib* pDib = pDoc->GetPDib();

	//��ȡDIB�ĳߴ�
	CSize sizeFileDib = pDib->GetDimensions();

	//��ʾDIB
	pDib->Draw(pDC, CPoint(0, 0), sizeFileDib);
}


// CMultimediaProjectView ��ӡ


void CMultimediaProjectView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMultimediaProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMultimediaProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMultimediaProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}

void CMultimediaProjectView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMultimediaProjectView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMultimediaProjectView ���

#ifdef _DEBUG
void CMultimediaProjectView::AssertValid() const
{
	CView::AssertValid();
}

void CMultimediaProjectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMultimediaProjectDoc* CMultimediaProjectView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMultimediaProjectDoc)));
	return (CMultimediaProjectDoc*)m_pDocument;
}
#endif //_DEBUG


// CMultimediaProjectView ��Ϣ�������


void CMultimediaProjectView::OnSingleThreshold()
{
	// TODO:  �ڴ���������������
	// ��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CMultimediaProjectDoc* pDoc = GetDocument();
	ImgDib* pDib = pDoc->GetPDib();

	//ֻ����Ҷ�ͼ��
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "ֻ����Ҷ�ͼ��", MB_OK, 0);
		return;
	}

	CSingleThresholdDlg dlgPara;
	if (dlgPara.DoModal() == IDOK)
	{
		int th = dlgPara.m_threshold;

		//�жϲ���������
		if (th < 0 || th > 255)
		{
			::MessageBox(0, "��ֵֻ������0~255֮�������", MB_OK, 0);
			return;
		}

		BinaryImg bImg(pDib->GetDimensions(), pDib->m_nBitCount,
		               pDib->m_lpColorTable, pDib->m_pImgData);
		bImg.singleThreshold(th);

		//�½�������ʾ
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		CMultimediaProjectView* pView = (CMultimediaProjectView*)pFrame->MDIGetActive()->GetActiveView();
		CMultimediaProjectDoc* pDocNew = pView->GetDocument();
		ImgDib* dibNew = pDocNew->GetPDib();
		dibNew->ReplaceDib(bImg.GetDimensions(), bImg.m_nBitCountOut, bImg.m_lpColorTableOut, bImg.m_pImgDataOut);
		pView->OnInitialUpdate();
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);
	}
}


void CMultimediaProjectView::OnDither()
{
	// TODO:  �ڴ���������������
	// ��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CMultimediaProjectDoc* pDoc = GetDocument();
	ImgDib* pDib = pDoc->GetPDib();

	//ֻ����Ҷ�ͼ��
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "ֻ����Ҷ�ͼ��", MB_OK, 0);
		return;
	}

	DitherDlg dlgPara;
	if (dlgPara.DoModal() == IDOK)
	{
		int Dn = dlgPara.m_Dn;

		//�жϲ���������
		if (Dn % 2 != 0 || Dn < 2)
		{
			::MessageBox(0, "ֻ��ѡ���СΪ2�ı�����Dither����", MB_OK, 0);
			return;
		}

		BinaryImg bImg(pDib->GetDimensions(), pDib->m_nBitCount,
		               pDib->m_lpColorTable, pDib->m_pImgData);
		bImg.dither(Dn);

		//�½�������ʾ
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		CMultimediaProjectView* pView = (CMultimediaProjectView*)pFrame->MDIGetActive()->GetActiveView();
		CMultimediaProjectDoc* pDocNew = pView->GetDocument();
		ImgDib* dibNew = pDocNew->GetPDib();
		dibNew->ReplaceDib(bImg.GetDimensions(), bImg.m_nBitCountOut, bImg.m_lpColorTableOut, bImg.m_pImgDataOut);
		pView->OnInitialUpdate();
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);
	}
}


void CMultimediaProjectView::OnOrderedDither()
{
	// TODO:  �ڴ���������������

	// ��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CMultimediaProjectDoc* pDoc = GetDocument();
	ImgDib* pDib = pDoc->GetPDib();

	//ֻ����Ҷ�ͼ��
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "ֻ����Ҷ�ͼ��", MB_OK, 0);
		return;
	}

	DitherDlg dlgPara;
	if (dlgPara.DoModal() == IDOK)
	{
		int Dn = dlgPara.m_Dn;

		//�жϲ���������
		if (Dn % 2 != 0 || Dn < 2)
		{
			::MessageBox(0, "ֻ��ѡ���СΪ2�ı�����Dither����", MB_OK, 0);
			return;
		}

		BinaryImg bImg(pDib->GetDimensions(), pDib->m_nBitCount,
		               pDib->m_lpColorTable, pDib->m_pImgData);
		bImg.orderedDither(Dn);

		//�½�������ʾ
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		CMultimediaProjectView* pView = (CMultimediaProjectView*)pFrame->MDIGetActive()->GetActiveView();
		CMultimediaProjectDoc* pDocNew = pView->GetDocument();
		ImgDib* dibNew = pDocNew->GetPDib();
		dibNew->ReplaceDib(bImg.GetDimensions(), bImg.m_nBitCountOut, bImg.m_lpColorTableOut, bImg.m_pImgDataOut);
		pView->OnInitialUpdate();
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);
	}
}

/***********************************************************************
* �������ƣ�
* UniformQuanlizationCR1()
*
*����������
*  ��
*
*����ֵ��
*   ��
*
*˵��������ѹ����Ϊ1�ľ�������
***********************************************************************/
void CMultimediaProjectView::UniformQuanlizationCR1()
{
	UniformQuanlizationCR(1);
}

/***********************************************************************
* �������ƣ�
* UniformQuanlizationCR2()
*
*����������
*  ��
*
*����ֵ��
*   ��
*
*˵��������ѹ����Ϊ2�ľ�������
***********************************************************************/
void CMultimediaProjectView::UniformQuanlizationCR2()
{
	UniformQuanlizationCR(2);
}

/***********************************************************************
* �������ƣ�
* UniformQuanlizationCR3()
*
*����������
*  ��
*
*����ֵ��
*   ��
*
*˵��������ѹ����Ϊ3�ľ�������
***********************************************************************/
void CMultimediaProjectView::UniformQuanlizationCR3()
{
	UniformQuanlizationCR(3);
}

/***********************************************************************
* �������ƣ�
* UniformQuanlizationCR4()
*
*����������
*  ��
*
*����ֵ��
*   ��
*
*˵��������ѹ����Ϊ4�ľ�������
***********************************************************************/
void CMultimediaProjectView::UniformQuanlizationCR4()
{
	UniformQuanlizationCR(4);
}

/***********************************************************************
* �������ƣ�
* UniformQuanlizationCR()
*
*����������
*  int cR ����ѹ����ΪcR�ľ�������
*
*����ֵ��
*   ��
*
*˵��������ѹ����ΪCR�ľ�������
***********************************************************************/
void CMultimediaProjectView::UniformQuanlizationCR(int cR)
{
	// TODO:  �ڴ���������������
	// ��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CMultimediaProjectDoc* pDoc = GetDocument();
	ImgDib* pDib = pDoc->GetPDib();

	//ֻ����Ҷ�ͼ��
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "ֻ����Ҷ�ͼ��", MB_OK, 0);
		return;
	}

	ImgDib newPdib(pDib->GetDimensions(), pDib->m_nBitCount,
	               pDib->m_lpColorTable, pDib->m_pImgData);
	newPdib.UniformQuanlization(cR); //����ѹ����ΪcR�ľ�������

	//�½�������ʾ
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMultimediaProjectView* pView = (CMultimediaProjectView*)pFrame->MDIGetActive()->GetActiveView();
	CMultimediaProjectDoc* pDocNew = pView->GetDocument();
	ImgDib* dibNew = pDocNew->GetPDib();
	dibNew->ReplaceDib(newPdib.GetDimensions(), newPdib.m_nBitCount, newPdib.m_lpColorTable, newPdib.m_pImgData);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}

/***********************************************************************
* �������ƣ�
* IGSUniformQuanlization()
*
*����������
*  ��
*
*����ֵ��
*   ��
*
*˵��������ѹ����Ϊ2�ĸĽ����IGS��������
***********************************************************************/
void CMultimediaProjectView::IGSUniformQuanlization()
{
	// ��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CMultimediaProjectDoc* pDoc = GetDocument();
	ImgDib* pDib = pDoc->GetPDib();

	//ֻ����Ҷ�ͼ��
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "ֻ����Ҷ�ͼ��", MB_OK, 0);
		return;
	}

	ImgDib newPdib(pDib->GetDimensions(), pDib->m_nBitCount,
	               pDib->m_lpColorTable, pDib->m_pImgData);
	newPdib.IGSUniformQuanlization(); //����ѹ����ΪcR�ľ�������

	//�½�������ʾ
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMultimediaProjectView* pView = (CMultimediaProjectView*)pFrame->MDIGetActive()->GetActiveView();
	CMultimediaProjectDoc* pDocNew = pView->GetDocument();
	ImgDib* dibNew = pDocNew->GetPDib();
	dibNew->ReplaceDib(newPdib.GetDimensions(), newPdib.m_nBitCount, newPdib.m_lpColorTable, newPdib.m_pImgData);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}

/***********************************************************************
* �������ƣ�
* ShowDCTTransform()
*
*����������
*  ��
*
*����ֵ��
*   ��
*
*˵��������DCT�任����չʾ�任���
***********************************************************************/
void CMultimediaProjectView::ShowDCTTransform()
{
	// ��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CMultimediaProjectDoc* pDoc = GetDocument();
	ImgDib* pDib = pDoc->GetPDib();

	//ֻ����Ҷ�ͼ��
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "ֻ����Ҷ�ͼ��", MB_OK, 0);
		return;
	}


	//��ȡ�û������DCT�任�������С
	CDCTDlg dlgPara;
	if (dlgPara.DoModal() == IDOK)
	{
		int width = dlgPara.m_width;
		int height = dlgPara.m_height;

		//�жϲ���������
		if (width <= 0 || height <= 0)
		{
			::MessageBox(0, "�������鲻��ȷ", MB_OK, 0);
			return;
		}

		//�жϲ���������
		if (width * height > 2500)
		{
			::MessageBox(0, "�����������������飬�����Ĵ�������ʱ��", MB_OK, 0);
			return;
		}

		ImgDib newPdib(pDib->GetDimensions(), pDib->m_nBitCount,
		               pDib->m_lpColorTable, pDib->m_pImgData);

		newPdib.DCTTransfrom(width, height); //����DCT�仯  
		// newPdib.InverseDCTTransfrom(width, height); //���б任֮���ٷ�DCT�任

		//�½�������ʾ
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		CMultimediaProjectView* pView = (CMultimediaProjectView*)pFrame->MDIGetActive()->GetActiveView();
		CMultimediaProjectDoc* pDocNew = pView->GetDocument();
		ImgDib* dibNew = pDocNew->GetPDib();
		dibNew->ReplaceDib(newPdib.GetDimensions(), newPdib.m_nBitCount, newPdib.m_lpColorTable, newPdib.m_pImgData);
		pView->OnInitialUpdate();
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);
	}
}

/***********************************************************************
* �������ƣ�
* ShowInverseDCTTransform()
*
*����������
*  ��
*
*����ֵ��
*   ��
*
*˵�������з�DCT�任����չʾ�任���
***********************************************************************/
void CMultimediaProjectView::ShowInverseDCTTransform()
{
	// ��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CMultimediaProjectDoc* pDoc = GetDocument();
	ImgDib* pDib = pDoc->GetPDib();

	//ֻ����Ҷ�ͼ��
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "ֻ����Ҷ�ͼ��", MB_OK, 0);
		return;
	}


	//��ȡ�û������DCT�任�������С
	CDCTDlg dlgPara;
	if (dlgPara.DoModal() == IDOK)
	{
		int width = dlgPara.m_width;
		int height = dlgPara.m_height;

		//�жϲ���������
		if (width <= 0 || height <= 0)
		{
			::MessageBox(0, "�������鲻��ȷ", MB_OK, 0);
			return;
		}

		//�жϲ���������
		if (width * height > 2500)
		{
			::MessageBox(0, "�����������������飬�����Ĵ�������ʱ��", MB_OK, 0);
			return;
		}

		//��ȡ�û�Ҫ���������ݶԻ���
		CReverseDCTDlg c_reverse_dct_dlg;
		if (c_reverse_dct_dlg.DoModal() == IDOK)
		{
			//��ȡҪ����������
			int abandon = c_reverse_dct_dlg.m_ratio;
			//�жϲ���������
			if (abandon < 0 | abandon > 100)
			{
				::MessageBox(0, "��������Ӧ����0~100֮��", MB_OK, 0);
				return;
			}

			ImgDib newPdib(pDib->GetDimensions(), pDib->m_nBitCount,
			               pDib->m_lpColorTable, pDib->m_pImgData);

			// newPdib.DCTTransfrom(width, height);//����DCT�仯  
			newPdib.InverseDCTTransfrom(width, height, abandon); //���б任֮���ٷ�DCT�任

			//�½�������ʾ
			CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
			pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
			CMultimediaProjectView* pView = (CMultimediaProjectView*)pFrame->MDIGetActive()->GetActiveView();
			CMultimediaProjectDoc* pDocNew = pView->GetDocument();
			ImgDib* dibNew = pDocNew->GetPDib();
			dibNew->ReplaceDib(newPdib.GetDimensions(), newPdib.m_nBitCount, newPdib.m_lpColorTable, newPdib.m_pImgData);
			pView->OnInitialUpdate();
			pDocNew->SetModifiedFlag(TRUE);
			pDocNew->UpdateAllViews(pView);
		}
	}
}

void CMultimediaProjectView::OnRGBToHSI()
{
	// TODO: �ڴ���������������
	//��ȡ�ĵ���ָ��
	CMultimediaProjectDoc* pDoc = GetDocument();
	//��ȡImgCenterDib�����m_dib��ָ�룬���ʵ�ǰDIB����
	ImgDib* pDib = pDoc->GetPDib();

	//ֻ�����ɫͼ��
	if (pDib->m_nBitCount != 24)
	{
		::MessageBox(0, "ֻ�����ɫͼ��",MB_OK, 0);
		return;
	}

	GrayTrans gImg(pDib->GetDimensions(), pDib->m_nBitCount,
	               pDib->m_lpColorTable, pDib->m_pImgData);
	gImg.RGBToHSI();

	//�½�������ʾ
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMultimediaProjectView* pView = (CMultimediaProjectView*)pFrame->MDIGetActive()->GetActiveView();
	CMultimediaProjectDoc* pDocNew = pView->GetDocument();
	ImgDib* dibNew = pDocNew->GetPDib();
	dibNew->ReplaceDib(gImg.GetDimensions(), gImg.m_nBitCountOut, gImg.m_lpColorTableOut, gImg.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}


void CMultimediaProjectView::OnRGBToYCbCr()
{
	// TODO: �ڴ���������������
	//��ȡ�ĵ���ָ��
	CMultimediaProjectDoc* pDoc = GetDocument();
	//��ȡImgCenterDib�����m_dib��ָ�룬���ʵ�ǰDIB����
	ImgDib* pDib = pDoc->GetPDib();

	//ֻ�����ɫͼ��
	if (pDib->m_nBitCount != 24)
	{
		::MessageBox(0, "ֻ�����ɫͼ��",MB_OK, 0);
		return;
	}

	GrayTrans gImg(pDib->GetDimensions(), pDib->m_nBitCount,
	               pDib->m_lpColorTable, pDib->m_pImgData);
	gImg.RGBToYCbCr();

	//�½�������ʾ
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMultimediaProjectView* pView = (CMultimediaProjectView*)pFrame->MDIGetActive()->GetActiveView();
	CMultimediaProjectDoc* pDocNew = pView->GetDocument();
	ImgDib* dibNew = pDocNew->GetPDib();
	dibNew->ReplaceDib(gImg.GetDimensions(), gImg.m_nBitCountOut, gImg.m_lpColorTableOut, gImg.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}


void CMultimediaProjectView::OnHistogram()
{
	// TODO: �ڴ���������������
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CMultimediaProjectDoc* pDoc = GetDocument();
	ImgDib* pDib = pDoc->GetPDib();

	//��pDib�е�ͼ��������Ϊ�������ݣ����ô������Ĺ��캯����
	//����Histogram��Ķ���hist
	Histogram hist(pDib->GetDimensions(), pDib->m_nBitCount,
	               pDib->m_lpColorTable, pDib->m_pImgData);

	//ֱ��ͼ����
	hist.histogram();

	//�½���ͼ���ڣ���ʾ�任���
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMultimediaProjectView* pView = (CMultimediaProjectView*)pFrame->MDIGetActive()->GetActiveView();
	CMultimediaProjectDoc* pDocNew = pView->GetDocument();
	ImgDib* dibNew = pDocNew->GetPDib();
	dibNew->ReplaceDib(hist.GetDimensions(), hist.m_nBitCount, hist.m_lpColorTable, hist.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}


void CMultimediaProjectView::OnxOneOrder()
{
	// TODO: �ڴ���������������
	//��ȡ�ĵ���ָ��
	CMultimediaProjectDoc* pDoc = GetDocument();
	//��ȡImgCenterDib�����m_dib��ָ�룬���ʵ�ǰDIB����
	ImgDib* pDib = pDoc->GetPDib();

	//ֻ����Ҷ�ͼ��
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "ֻ����8-bit�Ҷ�ͼ��",MB_OK, 0);
		return;
	}

	CXOneOrderDlg dlg1Para;
	if (dlg1Para.DoModal() == IDOK)
	{
		double a = dlg1Para.m_editax;

		//�жϲ���������
		if (a < 0 || a > 1)
		{
			::MessageBox(0, "ϵ��ֻ������0~1֮�����", MB_OK, 0);
			return;
		}

		LosslessPredictiveCoding lImg(pDib->GetDimensions(), pDib->m_nBitCount,
		                              pDib->m_lpColorTable, pDib->m_pImgData);
		lImg.xOneOrderLinearPrediction(a);

		//�½�������ʾ
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		CMultimediaProjectView* pView = (CMultimediaProjectView*)pFrame->MDIGetActive()->GetActiveView();
		CMultimediaProjectDoc* pDocNew = pView->GetDocument();
		ImgDib* dibNew = pDocNew->GetPDib();
		dibNew->ReplaceDib(lImg.GetDimensions(), lImg.m_nBitCountOut, lImg.m_lpColorTableOut, lImg.m_pImgDataOut);
		pView->OnInitialUpdate();
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);
	}
}


void CMultimediaProjectView::OnyOneOrder()
{
	// TODO: �ڴ���������������
	//��ȡ�ĵ���ָ��
	CMultimediaProjectDoc* pDoc = GetDocument();
	//��ȡImgCenterDib�����m_dib��ָ�룬���ʵ�ǰDIB����
	ImgDib* pDib = pDoc->GetPDib();

	//ֻ����Ҷ�ͼ��
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "ֻ����8-bit�Ҷ�ͼ��",MB_OK, 0);
		return;
	}

	CYOneOrderDlg dlg1Para;
	if (dlg1Para.DoModal() == IDOK)
	{
		double a = dlg1Para.m_editay;

		//�жϲ���������
		if (a < 0 || a > 1)
		{
			::MessageBox(0, "ϵ��ֻ������0~1֮�����", MB_OK, 0);
			return;
		}

		LosslessPredictiveCoding lImg(pDib->GetDimensions(), pDib->m_nBitCount,
		                              pDib->m_lpColorTable, pDib->m_pImgData);
		lImg.yOneOrderLinearPrediction(a);

		//�½�������ʾ
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		CMultimediaProjectView* pView = (CMultimediaProjectView*)pFrame->MDIGetActive()->GetActiveView();
		CMultimediaProjectDoc* pDocNew = pView->GetDocument();
		ImgDib* dibNew = pDocNew->GetPDib();
		dibNew->ReplaceDib(lImg.GetDimensions(), lImg.m_nBitCountOut, lImg.m_lpColorTableOut, lImg.m_pImgDataOut);
		pView->OnInitialUpdate();
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);
	}
}


void CMultimediaProjectView::OntwoOrder()
{
	// TODO: �ڴ���������������
	//��ȡ�ĵ���ָ��
	CMultimediaProjectDoc* pDoc = GetDocument();
	//��ȡImgCenterDib�����m_dib��ָ�룬���ʵ�ǰDIB����
	ImgDib* pDib = pDoc->GetPDib();

	//ֻ����Ҷ�ͼ��
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "ֻ����8-bit�Ҷ�ͼ��",MB_OK, 0);
		return;
	}

	CTwoOrderDlg dlg2Para;
	if (dlg2Para.DoModal() == IDOK)
	{
		double a1 = dlg2Para.m_editA1;
		double a2 = dlg2Para.m_editA2;

		//�жϲ���������
		if ((a1 < 0 || a1 > 1) || (a2 < 0 || a2 > 1))
		{
			::MessageBox(0, "ϵ��ֻ������0~1֮�����", MB_OK, 0);
			return;
		}
		else if (a1 + a2 > 1)
		{
			::MessageBox(0, "ϵ��a1��a2֮����С�ڵ���1", MB_OK, 0);
			return;
		}

		LosslessPredictiveCoding lImg(pDib->GetDimensions(), pDib->m_nBitCount,
		                              pDib->m_lpColorTable, pDib->m_pImgData);
		lImg.twoOrderLinearPrediction(a1, a2);

		//�½�������ʾ
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		CMultimediaProjectView* pView = (CMultimediaProjectView*)pFrame->MDIGetActive()->GetActiveView();
		CMultimediaProjectDoc* pDocNew = pView->GetDocument();
		ImgDib* dibNew = pDocNew->GetPDib();
		dibNew->ReplaceDib(lImg.GetDimensions(), lImg.m_nBitCountOut, lImg.m_lpColorTableOut, lImg.m_pImgDataOut);
		pView->OnInitialUpdate();
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);
	}
}


void CMultimediaProjectView::OnthreeOrder()
{
	// TODO: �ڴ���������������
	//��ȡ�ĵ���ָ��
	CMultimediaProjectDoc* pDoc = GetDocument();
	//��ȡImgCenterDib�����m_dib��ָ�룬���ʵ�ǰDIB����
	ImgDib* pDib = pDoc->GetPDib();

	//ֻ����Ҷ�ͼ��
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "ֻ����8-bit�Ҷ�ͼ��",MB_OK, 0);
		return;
	}

	CThreeOrderDlg dlg3Para;
	if (dlg3Para.DoModal() == IDOK)
	{
		double a1 = dlg3Para.m_edita1;
		double a2 = dlg3Para.m_edita2;
		double a3 = dlg3Para.m_edita3;

		//�жϲ���������
		if (a1 > 1 || a2 > 1 || a3 > 1)
		{
			::MessageBox(0, "ϵ��ֻ������С��1֮�����", MB_OK, 0);
			return;
		}
		else if (a1 + a2 + a3 > 1)
		{
			::MessageBox(0, "ϵ��a1,a2��a3֮����С�ڵ���1", MB_OK, 0);
			return;
		}

		LosslessPredictiveCoding lImg(pDib->GetDimensions(), pDib->m_nBitCount,
		                              pDib->m_lpColorTable, pDib->m_pImgData);
		lImg.threeOrderLinearPrediction(a1, a2, a3);

		//�½�������ʾ
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		CMultimediaProjectView* pView = (CMultimediaProjectView*)pFrame->MDIGetActive()->GetActiveView();
		CMultimediaProjectDoc* pDocNew = pView->GetDocument();
		ImgDib* dibNew = pDocNew->GetPDib();
		dibNew->ReplaceDib(lImg.GetDimensions(), lImg.m_nBitCountOut, lImg.m_lpColorTableOut, lImg.m_pImgDataOut);
		pView->OnInitialUpdate();
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);
	}
}


void CMultimediaProjectView::OnHistogramDraw()
{
	// TODO: �ڴ���������������
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CMultimediaProjectDoc* pDoc = GetDocument();
	ImgDib* pDib = pDoc->GetPDib();

	//�쳣�ж�
	if (pDib->m_nBitCount != 8 && pDib->m_nBitCount != 24)
	{
		::MessageBox(0, "ֻ����ҶȺͲ�ɫͼ��",MB_OK, 0);
		return;
	}

	//ֱ��ͼ���ƶԻ���
	CHistogramDrawDlg dlgHist;
	dlgHist.m_histogramDib.ReplaceDib(pDib->GetDimensions(), pDib->m_nBitCount,
	                                  pDib->m_lpColorTable, pDib->m_pImgData);

	//��ʾֱ��ͼ
	dlgHist.DoModal();
}


void CMultimediaProjectView::OnHuffman()
{
	// TODO:  �ڴ���������������
	//��ȡ�ĵ���ָ��
	CMultimediaProjectDoc* pDoc = GetDocument();
	//��ȡImgCenterDib�����m_dib��ָ�룬���ʵ�ǰDIB����
	ImgDib* pDib = pDoc->GetPDib();

	//ֻ����Ҷ�ͼ��
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "ֻ����8-bit�Ҷ�ͼ��", MB_OK, 0);
		return;
	}

	HuffmanCoding Img(pDib->GetDimensions(), pDib->m_nBitCount,
	                  pDib->m_lpColorTable, pDib->m_pImgData);
	Img.coding();

	/***************************************************
	������������������
	���öԻ�����ʾ���������
	****************************************************/

	// �����Ի���
	CHuffmanDlg dlgCoding;

	// ��ʼ������ֵ
	dlgCoding.dProba = Img.dProba;
	dlgCoding.nColorNum = 256;

	// ��ʾ�Ի���
	dlgCoding.DoModal();
}
