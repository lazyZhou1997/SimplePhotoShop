// MultimediaProjectView.cpp : CMultimediaProjectView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
		// 标准打印命令
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMultimediaProjectView::OnFilePrintPreview)
		ON_WM_CONTEXTMENU()
		ON_WM_RBUTTONUP()
		ON_COMMAND(ID_32773, &CMultimediaProjectView::OnSingleThreshold)
		ON_COMMAND(ID_32774, &CMultimediaProjectView::OnDither)
		ON_COMMAND(ID_32775, &CMultimediaProjectView::OnOrderedDither)
		ON_COMMAND(ID_32783, &CMultimediaProjectView::UniformQuanlizationCR1) //CR为1的均匀量化
		ON_COMMAND(ID_32784, &CMultimediaProjectView::UniformQuanlizationCR2) //CR为2的均匀量化
		ON_COMMAND(ID_32785, &CMultimediaProjectView::UniformQuanlizationCR3) //CR为3的均匀量化
		ON_COMMAND(ID_32786, &CMultimediaProjectView::UniformQuanlizationCR4) //CR为4的均匀量化
		ON_COMMAND(ID_32787, &CMultimediaProjectView::IGSUniformQuanlization) //CR为2改进的IGS的均匀量化
		ON_COMMAND(ID_32780, &CMultimediaProjectView::ShowDCTTransform) //进行DCT变化
		ON_COMMAND(ID_32781, &CMultimediaProjectView::ShowInverseDCTTransform) //进行反DCT变化
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

// CMultimediaProjectView 构造/析构

CMultimediaProjectView::CMultimediaProjectView()
{
	// TODO:  在此处添加构造代码
}

CMultimediaProjectView::~CMultimediaProjectView()
{
}

BOOL CMultimediaProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMultimediaProjectView 绘制

void CMultimediaProjectView::OnDraw(CDC* pDC)
{
	CMultimediaProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码

	//返回myDib的指针
	ImgDib* pDib = pDoc->GetPDib();

	//获取DIB的尺寸
	CSize sizeFileDib = pDib->GetDimensions();

	//显示DIB
	pDib->Draw(pDC, CPoint(0, 0), sizeFileDib);
}


// CMultimediaProjectView 打印


void CMultimediaProjectView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMultimediaProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMultimediaProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMultimediaProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
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


// CMultimediaProjectView 诊断

#ifdef _DEBUG
void CMultimediaProjectView::AssertValid() const
{
	CView::AssertValid();
}

void CMultimediaProjectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMultimediaProjectDoc* CMultimediaProjectView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMultimediaProjectDoc)));
	return (CMultimediaProjectDoc*)m_pDocument;
}
#endif //_DEBUG


// CMultimediaProjectView 消息处理程序


void CMultimediaProjectView::OnSingleThreshold()
{
	// TODO:  在此添加命令处理程序代码
	// 获取文档类中m_dib的指针，访问当前DIB数据
	CMultimediaProjectDoc* pDoc = GetDocument();
	ImgDib* pDib = pDoc->GetPDib();

	//只处理灰度图像
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "只处理灰度图像", MB_OK, 0);
		return;
	}

	CSingleThresholdDlg dlgPara;
	if (dlgPara.DoModal() == IDOK)
	{
		int th = dlgPara.m_threshold;

		//判断参数合理性
		if (th < 0 || th > 255)
		{
			::MessageBox(0, "阈值只能设置0~255之间的整数", MB_OK, 0);
			return;
		}

		BinaryImg bImg(pDib->GetDimensions(), pDib->m_nBitCount,
		               pDib->m_lpColorTable, pDib->m_pImgData);
		bImg.singleThreshold(th);

		//新建窗口显示
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
	// TODO:  在此添加命令处理程序代码
	// 获取文档类中m_dib的指针，访问当前DIB数据
	CMultimediaProjectDoc* pDoc = GetDocument();
	ImgDib* pDib = pDoc->GetPDib();

	//只处理灰度图像
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "只处理灰度图像", MB_OK, 0);
		return;
	}

	DitherDlg dlgPara;
	if (dlgPara.DoModal() == IDOK)
	{
		int Dn = dlgPara.m_Dn;

		//判断参数合理性
		if (Dn % 2 != 0 || Dn < 2)
		{
			::MessageBox(0, "只能选择大小为2的倍数的Dither矩阵", MB_OK, 0);
			return;
		}

		BinaryImg bImg(pDib->GetDimensions(), pDib->m_nBitCount,
		               pDib->m_lpColorTable, pDib->m_pImgData);
		bImg.dither(Dn);

		//新建窗口显示
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
	// TODO:  在此添加命令处理程序代码

	// 获取文档类中m_dib的指针，访问当前DIB数据
	CMultimediaProjectDoc* pDoc = GetDocument();
	ImgDib* pDib = pDoc->GetPDib();

	//只处理灰度图像
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "只处理灰度图像", MB_OK, 0);
		return;
	}

	DitherDlg dlgPara;
	if (dlgPara.DoModal() == IDOK)
	{
		int Dn = dlgPara.m_Dn;

		//判断参数合理性
		if (Dn % 2 != 0 || Dn < 2)
		{
			::MessageBox(0, "只能选择大小为2的倍数的Dither矩阵", MB_OK, 0);
			return;
		}

		BinaryImg bImg(pDib->GetDimensions(), pDib->m_nBitCount,
		               pDib->m_lpColorTable, pDib->m_pImgData);
		bImg.orderedDither(Dn);

		//新建窗口显示
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
* 函数名称：
* UniformQuanlizationCR1()
*
*函数参数：
*  无
*
*返回值：
*   无
*
*说明：进行压缩比为1的均匀量化
***********************************************************************/
void CMultimediaProjectView::UniformQuanlizationCR1()
{
	UniformQuanlizationCR(1);
}

/***********************************************************************
* 函数名称：
* UniformQuanlizationCR2()
*
*函数参数：
*  无
*
*返回值：
*   无
*
*说明：进行压缩比为2的均匀量化
***********************************************************************/
void CMultimediaProjectView::UniformQuanlizationCR2()
{
	UniformQuanlizationCR(2);
}

/***********************************************************************
* 函数名称：
* UniformQuanlizationCR3()
*
*函数参数：
*  无
*
*返回值：
*   无
*
*说明：进行压缩比为3的均匀量化
***********************************************************************/
void CMultimediaProjectView::UniformQuanlizationCR3()
{
	UniformQuanlizationCR(3);
}

/***********************************************************************
* 函数名称：
* UniformQuanlizationCR4()
*
*函数参数：
*  无
*
*返回值：
*   无
*
*说明：进行压缩比为4的均匀量化
***********************************************************************/
void CMultimediaProjectView::UniformQuanlizationCR4()
{
	UniformQuanlizationCR(4);
}

/***********************************************************************
* 函数名称：
* UniformQuanlizationCR()
*
*函数参数：
*  int cR 进行压缩比为cR的均匀量化
*
*返回值：
*   无
*
*说明：进行压缩比为CR的均匀量化
***********************************************************************/
void CMultimediaProjectView::UniformQuanlizationCR(int cR)
{
	// TODO:  在此添加命令处理程序代码
	// 获取文档类中m_dib的指针，访问当前DIB数据
	CMultimediaProjectDoc* pDoc = GetDocument();
	ImgDib* pDib = pDoc->GetPDib();

	//只处理灰度图像
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "只处理灰度图像", MB_OK, 0);
		return;
	}

	ImgDib newPdib(pDib->GetDimensions(), pDib->m_nBitCount,
	               pDib->m_lpColorTable, pDib->m_pImgData);
	newPdib.UniformQuanlization(cR); //进行压缩比为cR的均匀量化

	//新建窗口显示
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
* 函数名称：
* IGSUniformQuanlization()
*
*函数参数：
*  无
*
*返回值：
*   无
*
*说明：进行压缩比为2的改进版的IGS均匀量化
***********************************************************************/
void CMultimediaProjectView::IGSUniformQuanlization()
{
	// 获取文档类中m_dib的指针，访问当前DIB数据
	CMultimediaProjectDoc* pDoc = GetDocument();
	ImgDib* pDib = pDoc->GetPDib();

	//只处理灰度图像
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "只处理灰度图像", MB_OK, 0);
		return;
	}

	ImgDib newPdib(pDib->GetDimensions(), pDib->m_nBitCount,
	               pDib->m_lpColorTable, pDib->m_pImgData);
	newPdib.IGSUniformQuanlization(); //进行压缩比为cR的均匀量化

	//新建窗口显示
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
* 函数名称：
* ShowDCTTransform()
*
*函数参数：
*  无
*
*返回值：
*   无
*
*说明：进行DCT变换并且展示变换结果
***********************************************************************/
void CMultimediaProjectView::ShowDCTTransform()
{
	// 获取文档类中m_dib的指针，访问当前DIB数据
	CMultimediaProjectDoc* pDoc = GetDocument();
	ImgDib* pDib = pDoc->GetPDib();

	//只处理灰度图像
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "只处理灰度图像", MB_OK, 0);
		return;
	}


	//获取用户输入的DCT变换的区块大小
	CDCTDlg dlgPara;
	if (dlgPara.DoModal() == IDOK)
	{
		int width = dlgPara.m_width;
		int height = dlgPara.m_height;

		//判断参数合理性
		if (width <= 0 || height <= 0)
		{
			::MessageBox(0, "输入区块不正确", MB_OK, 0);
			return;
		}

		//判断参数合理性
		if (width * height > 2500)
		{
			::MessageBox(0, "不建议输入过大的区块，会消耗大量运算时间", MB_OK, 0);
			return;
		}

		ImgDib newPdib(pDib->GetDimensions(), pDib->m_nBitCount,
		               pDib->m_lpColorTable, pDib->m_pImgData);

		newPdib.DCTTransfrom(width, height); //进行DCT变化  
		// newPdib.InverseDCTTransfrom(width, height); //进行变换之后再反DCT变换

		//新建窗口显示
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
* 函数名称：
* ShowInverseDCTTransform()
*
*函数参数：
*  无
*
*返回值：
*   无
*
*说明：进行反DCT变换并且展示变换结果
***********************************************************************/
void CMultimediaProjectView::ShowInverseDCTTransform()
{
	// 获取文档类中m_dib的指针，访问当前DIB数据
	CMultimediaProjectDoc* pDoc = GetDocument();
	ImgDib* pDib = pDoc->GetPDib();

	//只处理灰度图像
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "只处理灰度图像", MB_OK, 0);
		return;
	}


	//获取用户输入的DCT变换的区块大小
	CDCTDlg dlgPara;
	if (dlgPara.DoModal() == IDOK)
	{
		int width = dlgPara.m_width;
		int height = dlgPara.m_height;

		//判断参数合理性
		if (width <= 0 || height <= 0)
		{
			::MessageBox(0, "输入区块不正确", MB_OK, 0);
			return;
		}

		//判断参数合理性
		if (width * height > 2500)
		{
			::MessageBox(0, "不建议输入过大的区块，会消耗大量运算时间", MB_OK, 0);
			return;
		}

		//获取用户要丢弃的数据对话框
		CReverseDCTDlg c_reverse_dct_dlg;
		if (c_reverse_dct_dlg.DoModal() == IDOK)
		{
			//获取要丢弃的数据
			int abandon = c_reverse_dct_dlg.m_ratio;
			//判断参数合理性
			if (abandon < 0 | abandon > 100)
			{
				::MessageBox(0, "输入数据应该在0~100之间", MB_OK, 0);
				return;
			}

			ImgDib newPdib(pDib->GetDimensions(), pDib->m_nBitCount,
			               pDib->m_lpColorTable, pDib->m_pImgData);

			// newPdib.DCTTransfrom(width, height);//进行DCT变化  
			newPdib.InverseDCTTransfrom(width, height, abandon); //进行变换之后再反DCT变换

			//新建窗口显示
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
	// TODO: 在此添加命令处理程序代码
	//获取文档类指针
	CMultimediaProjectDoc* pDoc = GetDocument();
	//获取ImgCenterDib类对象m_dib的指针，访问当前DIB数据
	ImgDib* pDib = pDoc->GetPDib();

	//只处理彩色图像
	if (pDib->m_nBitCount != 24)
	{
		::MessageBox(0, "只处理彩色图像",MB_OK, 0);
		return;
	}

	GrayTrans gImg(pDib->GetDimensions(), pDib->m_nBitCount,
	               pDib->m_lpColorTable, pDib->m_pImgData);
	gImg.RGBToHSI();

	//新建窗口显示
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
	// TODO: 在此添加命令处理程序代码
	//获取文档类指针
	CMultimediaProjectDoc* pDoc = GetDocument();
	//获取ImgCenterDib类对象m_dib的指针，访问当前DIB数据
	ImgDib* pDib = pDoc->GetPDib();

	//只处理彩色图像
	if (pDib->m_nBitCount != 24)
	{
		::MessageBox(0, "只处理彩色图像",MB_OK, 0);
		return;
	}

	GrayTrans gImg(pDib->GetDimensions(), pDib->m_nBitCount,
	               pDib->m_lpColorTable, pDib->m_pImgData);
	gImg.RGBToYCbCr();

	//新建窗口显示
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
	// TODO: 在此添加命令处理程序代码
	//获取文档类中m_dib的指针，访问当前DIB数据
	CMultimediaProjectDoc* pDoc = GetDocument();
	ImgDib* pDib = pDoc->GetPDib();

	//将pDib中的图像数据作为输入数据，调用带参数的构造函数，
	//定义Histogram类的对象hist
	Histogram hist(pDib->GetDimensions(), pDib->m_nBitCount,
	               pDib->m_lpColorTable, pDib->m_pImgData);

	//直方图均衡
	hist.histogram();

	//新建视图窗口，显示变换结果
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
	// TODO: 在此添加命令处理程序代码
	//获取文档类指针
	CMultimediaProjectDoc* pDoc = GetDocument();
	//获取ImgCenterDib类对象m_dib的指针，访问当前DIB数据
	ImgDib* pDib = pDoc->GetPDib();

	//只处理灰度图像
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "只处理8-bit灰度图像",MB_OK, 0);
		return;
	}

	CXOneOrderDlg dlg1Para;
	if (dlg1Para.DoModal() == IDOK)
	{
		double a = dlg1Para.m_editax;

		//判断参数合理性
		if (a < 0 || a > 1)
		{
			::MessageBox(0, "系数只能设置0~1之间的数", MB_OK, 0);
			return;
		}

		LosslessPredictiveCoding lImg(pDib->GetDimensions(), pDib->m_nBitCount,
		                              pDib->m_lpColorTable, pDib->m_pImgData);
		lImg.xOneOrderLinearPrediction(a);

		//新建窗口显示
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
	// TODO: 在此添加命令处理程序代码
	//获取文档类指针
	CMultimediaProjectDoc* pDoc = GetDocument();
	//获取ImgCenterDib类对象m_dib的指针，访问当前DIB数据
	ImgDib* pDib = pDoc->GetPDib();

	//只处理灰度图像
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "只处理8-bit灰度图像",MB_OK, 0);
		return;
	}

	CYOneOrderDlg dlg1Para;
	if (dlg1Para.DoModal() == IDOK)
	{
		double a = dlg1Para.m_editay;

		//判断参数合理性
		if (a < 0 || a > 1)
		{
			::MessageBox(0, "系数只能设置0~1之间的数", MB_OK, 0);
			return;
		}

		LosslessPredictiveCoding lImg(pDib->GetDimensions(), pDib->m_nBitCount,
		                              pDib->m_lpColorTable, pDib->m_pImgData);
		lImg.yOneOrderLinearPrediction(a);

		//新建窗口显示
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
	// TODO: 在此添加命令处理程序代码
	//获取文档类指针
	CMultimediaProjectDoc* pDoc = GetDocument();
	//获取ImgCenterDib类对象m_dib的指针，访问当前DIB数据
	ImgDib* pDib = pDoc->GetPDib();

	//只处理灰度图像
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "只处理8-bit灰度图像",MB_OK, 0);
		return;
	}

	CTwoOrderDlg dlg2Para;
	if (dlg2Para.DoModal() == IDOK)
	{
		double a1 = dlg2Para.m_editA1;
		double a2 = dlg2Para.m_editA2;

		//判断参数合理性
		if ((a1 < 0 || a1 > 1) || (a2 < 0 || a2 > 1))
		{
			::MessageBox(0, "系数只能设置0~1之间的数", MB_OK, 0);
			return;
		}
		else if (a1 + a2 > 1)
		{
			::MessageBox(0, "系数a1与a2之和需小于等于1", MB_OK, 0);
			return;
		}

		LosslessPredictiveCoding lImg(pDib->GetDimensions(), pDib->m_nBitCount,
		                              pDib->m_lpColorTable, pDib->m_pImgData);
		lImg.twoOrderLinearPrediction(a1, a2);

		//新建窗口显示
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
	// TODO: 在此添加命令处理程序代码
	//获取文档类指针
	CMultimediaProjectDoc* pDoc = GetDocument();
	//获取ImgCenterDib类对象m_dib的指针，访问当前DIB数据
	ImgDib* pDib = pDoc->GetPDib();

	//只处理灰度图像
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "只处理8-bit灰度图像",MB_OK, 0);
		return;
	}

	CThreeOrderDlg dlg3Para;
	if (dlg3Para.DoModal() == IDOK)
	{
		double a1 = dlg3Para.m_edita1;
		double a2 = dlg3Para.m_edita2;
		double a3 = dlg3Para.m_edita3;

		//判断参数合理性
		if (a1 > 1 || a2 > 1 || a3 > 1)
		{
			::MessageBox(0, "系数只能设置小于1之间的数", MB_OK, 0);
			return;
		}
		else if (a1 + a2 + a3 > 1)
		{
			::MessageBox(0, "系数a1,a2与a3之和需小于等于1", MB_OK, 0);
			return;
		}

		LosslessPredictiveCoding lImg(pDib->GetDimensions(), pDib->m_nBitCount,
		                              pDib->m_lpColorTable, pDib->m_pImgData);
		lImg.threeOrderLinearPrediction(a1, a2, a3);

		//新建窗口显示
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
	// TODO: 在此添加命令处理程序代码
	//获取文档类中m_dib的指针，访问当前DIB数据
	CMultimediaProjectDoc* pDoc = GetDocument();
	ImgDib* pDib = pDoc->GetPDib();

	//异常判断
	if (pDib->m_nBitCount != 8 && pDib->m_nBitCount != 24)
	{
		::MessageBox(0, "只处理灰度和彩色图像",MB_OK, 0);
		return;
	}

	//直方图绘制对话框
	CHistogramDrawDlg dlgHist;
	dlgHist.m_histogramDib.ReplaceDib(pDib->GetDimensions(), pDib->m_nBitCount,
	                                  pDib->m_lpColorTable, pDib->m_pImgData);

	//显示直方图
	dlgHist.DoModal();
}


void CMultimediaProjectView::OnHuffman()
{
	// TODO:  在此添加命令处理程序代码
	//获取文档类指针
	CMultimediaProjectDoc* pDoc = GetDocument();
	//获取ImgCenterDib类对象m_dib的指针，访问当前DIB数据
	ImgDib* pDib = pDoc->GetPDib();

	//只处理灰度图像
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "只处理8-bit灰度图像", MB_OK, 0);
		return;
	}

	HuffmanCoding Img(pDib->GetDimensions(), pDib->m_nBitCount,
	                  pDib->m_lpColorTable, pDib->m_pImgData);
	Img.coding();

	/***************************************************
	构建霍夫曼编码的码表
	并用对话框显示霍夫曼码表
	****************************************************/

	// 创建对话框
	CHuffmanDlg dlgCoding;

	// 初始化变量值
	dlgCoding.dProba = Img.dProba;
	dlgCoding.nColorNum = 256;

	// 显示对话框
	dlgCoding.DoModal();
}
