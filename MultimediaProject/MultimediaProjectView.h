
// MultimediaProjectView.h : CMultimediaProjectView ��Ľӿ�
//

#pragma once


class CMultimediaProjectView : public CView
{
protected: // �������л�����
	CMultimediaProjectView();
	DECLARE_DYNCREATE(CMultimediaProjectView)

// ����
public:
	CMultimediaProjectDoc* GetDocument() const;
	void UniformQuanlizationCR(int cR);//ѹ����ΪcR�ĵľ�������

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMultimediaProjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSingleThreshold();
	afx_msg void OnDither();
	afx_msg void OnOrderedDither();
	afx_msg void UniformQuanlizationCR1();//CRΪ1�ľ�������
	afx_msg void UniformQuanlizationCR2();//CRΪ2�ľ�������
	afx_msg void UniformQuanlizationCR3();//CRΪ3�ľ�������
	afx_msg void UniformQuanlizationCR4();//CRΪ4�ľ�������
	afx_msg void IGSUniformQuanlization();//CRΪ2�Ľ���IGS�ľ�������
	afx_msg void ShowDCTTransform();//����DCT�仯
	afx_msg void ShowInverseDCTTransform();//���з�DCT�仯
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

#ifndef _DEBUG  // MultimediaProjectView.cpp �еĵ��԰汾
inline CMultimediaProjectDoc* CMultimediaProjectView::GetDocument() const
   { return reinterpret_cast<CMultimediaProjectDoc*>(m_pDocument); }
#endif

