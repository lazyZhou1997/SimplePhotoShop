
// MultimediaProjectDoc.cpp : CMultimediaProjectDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MultimediaProject.h"
#endif

#include "MultimediaProjectDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMultimediaProjectDoc

IMPLEMENT_DYNCREATE(CMultimediaProjectDoc, CDocument)

BEGIN_MESSAGE_MAP(CMultimediaProjectDoc, CDocument)
END_MESSAGE_MAP()


// CMultimediaProjectDoc ����/����

CMultimediaProjectDoc::CMultimediaProjectDoc()
{
	// TODO:  �ڴ����һ���Թ������

}

CMultimediaProjectDoc::~CMultimediaProjectDoc()
{
}

BOOL CMultimediaProjectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMultimediaProjectDoc ���л�

void CMultimediaProjectDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  �ڴ���Ӵ洢����
	}
	else
	{
		// TODO:  �ڴ���Ӽ��ش���
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMultimediaDoc commands

// �����ļ�
BOOL CMultimediaProjectDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	if(myDib.Write(lpszPathName) == TRUE)	{
		SetModifiedFlag(FALSE);     // have saved
		return TRUE;
	}
	else 
		return 0;
}

// ���ļ�
BOOL CMultimediaProjectDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (myDib.Read(lpszPathName) == TRUE) {	
		SetModifiedFlag(FALSE);     // start off with unmodified
		return TRUE;
	}
	else 
		return 0;
}


#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CMultimediaProjectDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CMultimediaProjectDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CMultimediaProjectDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMultimediaProjectDoc ���

#ifdef _DEBUG
void CMultimediaProjectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMultimediaProjectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMultimediaProjectDoc ����
