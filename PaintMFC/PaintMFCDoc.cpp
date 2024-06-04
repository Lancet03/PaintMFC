
// PaintMFCDoc.cpp : implementation of the CPaintMFCDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PaintMFC.h"
#endif

#include "PaintMFCDoc.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CTriangle.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPaintMFCDoc

IMPLEMENT_DYNCREATE(CPaintMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CPaintMFCDoc, CDocument)
END_MESSAGE_MAP()


// CPaintMFCDoc construction/destruction

CPaintMFCDoc::CPaintMFCDoc() noexcept
{
	// TODO: add one-time construction code here

}

CPaintMFCDoc::~CPaintMFCDoc()
{
}

BOOL CPaintMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CPaintMFCDoc serialization

void CPaintMFCDoc::Serialize(CArchive& ar)
{
	INT_PTR num = 0;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		num = m_figures.GetCount();
		ar << num;
		for (int i = 0; i < num; i++) {
			ar << m_figures[i]->figureType;
			ar << m_figures[i]->x;
			ar << m_figures[i]->y;
			ar << m_figures[i]->width;
			ar << m_figures[i]->height;
		}
	}
	else
	{
		// TODO: add loading code here
		ar >> num;
		for (int i = 0; i < num; i++) {
			CFigure* r;
			int figType;
			ar >> figType;
			if (figType == 1) {
				r = new CRectangle();
			}
			else if (figType == 2) {
				r = new CCircle();
			}
			else if (figType == 3) {
				r = new CTriangle();
			}
			else {
				r = new CRectangle();
			}
			ar >> r->x;
			ar >> r->y;
			ar >> r->width;
			ar >> r->height;
		
			this->m_figures.Add(r);
		}

	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CPaintMFCDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
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

// Support for Search Handlers
void CPaintMFCDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CPaintMFCDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CPaintMFCDoc diagnostics

#ifdef _DEBUG
void CPaintMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPaintMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPaintMFCDoc commands


void CPaintMFCDoc::DeleteContents()
{
	// TODO: Add your specialized code here and/or call the base class
	this->m_figures.RemoveAll();

	CDocument::DeleteContents();
}
