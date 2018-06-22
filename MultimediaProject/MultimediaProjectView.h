
// MultimediaProjectView.h : CMultimediaProjectView 类的接口
//

#pragma once


class CMultimediaProjectView : public CView
{
protected: // 仅从序列化创建
	CMultimediaProjectView();
	DECLARE_DYNCREATE(CMultimediaProjectView)

// 特性
public:
	CMultimediaProjectDoc* GetDocument() const;
	void UniformQuanlizationCR(int cR);//压缩比为cR的的均匀量化

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMultimediaProjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSingleThreshold();
	afx_msg void OnDither();
	afx_msg void OnOrderedDither();
	afx_msg void UniformQuanlizationCR1();//CR为1的均匀量化
	afx_msg void UniformQuanlizationCR2();//CR为2的均匀量化
	afx_msg void UniformQuanlizationCR3();//CR为3的均匀量化
	afx_msg void UniformQuanlizationCR4();//CR为4的均匀量化
	afx_msg void IGSUniformQuanlization();//CR为2改进的IGS的均匀量化
	afx_msg void ShowDCTTransform();//进行DCT变化
	afx_msg void ShowInverseDCTTransform();//进行反DCT变化
	afx_msg void OnRGBToHSI();
	afx_msg void OnRGBToYCbCr();
	afx_msg void OnHistogram();
	afx_msg void OnxOneOrder();
	afx_msg void OnyOneOrder();
	afx_msg void OntwoOrder();
	afx_msg void OnthreeOrder();
	afx_msg void OnHistogramDraw();
	afx_msg void OnHuffman();
};

#ifndef _DEBUG  // MultimediaProjectView.cpp 中的调试版本
inline CMultimediaProjectDoc* CMultimediaProjectView::GetDocument() const
   { return reinterpret_cast<CMultimediaProjectDoc*>(m_pDocument); }
#endif

