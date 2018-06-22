
// MultimediaProjectDoc.h : CMultimediaProjectDoc 类的接口
//

#include "ImgDib.h"
#pragma once


class CMultimediaProjectDoc : public CDocument
{
protected: // 仅从序列化创建
	CMultimediaProjectDoc();
	DECLARE_DYNCREATE(CMultimediaProjectDoc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMultimediaProjectDoc();

	//获取myDib的指针
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
	//ImgDib类的对象，从打开文件中读入的数据放在该对象中
	ImgDib myDib;

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
