
// MultimediaProjectDoc.h : CMultimediaProjectDoc ��Ľӿ�
//

#include "ImgDib.h"
#pragma once


class CMultimediaProjectDoc : public CDocument
{
protected: // �������л�����
	CMultimediaProjectDoc();
	DECLARE_DYNCREATE(CMultimediaProjectDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMultimediaProjectDoc();

	//��ȡmyDib��ָ��
	ImgDib *GetPDib()
	{
		return &myDib;
	}

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

private:
	//ImgDib��Ķ��󣬴Ӵ��ļ��ж�������ݷ��ڸö�����
	ImgDib myDib;

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
