
// PaintMFCView.cpp : implementation of the CPaintMFCView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PaintMFC.h"
#endif

#include "PaintMFCDoc.h"
#include "PaintMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPaintMFCView

IMPLEMENT_DYNCREATE(CPaintMFCView, CView)

BEGIN_MESSAGE_MAP(CPaintMFCView, CView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CPaintMFCView construction/destruction

CPaintMFCView::CPaintMFCView() noexcept
{
	// TODO: add construction code here

}

CPaintMFCView::~CPaintMFCView()
{
}

BOOL CPaintMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPaintMFCView drawing

void CPaintMFCView::OnDraw(CDC* /*pDC*/)
{
	CPaintMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CPaintMFCView diagnostics

#ifdef _DEBUG
void CPaintMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CPaintMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPaintMFCDoc* CPaintMFCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPaintMFCDoc)));
	return (CPaintMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CPaintMFCView message handlers


void CPaintMFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonDown(nFlags, point);
}
