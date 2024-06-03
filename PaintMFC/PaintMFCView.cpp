
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

#include "CRectangle.h"
#include "CFigure.h"

#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPaintMFCView

IMPLEMENT_DYNCREATE(CPaintMFCView, CView)

BEGIN_MESSAGE_MAP(CPaintMFCView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYUP()
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

void CPaintMFCView::OnDraw(CDC* pDC)
{
	CPaintMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	for (int i = 0; i < pDoc->m_figures.GetCount(); i++) {
		CPen pen;
		CPen* oldPen = NULL;

		if (this->m_selected == i) {
			pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			oldPen = pDC->SelectObject(&pen);
		}

		auto r = pDoc->m_figures.GetAt(i);
		/*pDC->Rectangle(r->x, r->y, r->x + r->width, r->y + r->height);*/
		r->DrawSelf(pDC);

		if (oldPen != NULL) {
			pDC->SelectObject(oldPen);
			oldPen->DeleteObject();
		}
	}

	if (this->m_bDrawInProgress) {
		this->figureInProgress->DrawSelf(pDC);
	}
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
	CClientDC dc(this);
	auto pDoc = GetDocument();

	int figNum = this->FindFigure(point);
	if (figNum > -1) {
		this->m_dragNumber = figNum;
		this->figureInProgress = pDoc->m_figures[figNum];
		/*this->figureInProgress->x = point.x;
		this->figureInProgress->y = point.y;*/
	}
	else {
		this->figureInProgress = new CRectangle();
		this->figureInProgress->x = point.x;
		this->figureInProgress->y = point.y;
		this->m_bDrawInProgress = TRUE;
	}

	CView::OnLButtonDown(nFlags, point);
}


void CPaintMFCView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (this->m_dragNumber > -1) {
		this->m_dragNumber = -1;
		this->figureInProgress = nullptr;
	}

	if (this->m_bDrawInProgress) {
		this->figureInProgress->width = point.x - this->figureInProgress->x;
		this->figureInProgress->height = point.y - this->figureInProgress->y;


		auto pDoc = GetDocument();
		pDoc->m_figures.Add(this->figureInProgress);

		pDoc->SetModifiedFlag(1);
		this->m_bDrawInProgress = FALSE;
		this->figureInProgress = nullptr;
	}


	InvalidateRect(NULL);
	CView::OnLButtonUp(nFlags, point);
}


void CPaintMFCView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (this->m_bDrawInProgress) {
		this->figureInProgress->width = point.x - this->figureInProgress->x;
		this->figureInProgress->height = point.y - this->figureInProgress->y;
		InvalidateRect(NULL);
	}

	if (this->m_dragNumber > -1) {
		int offsetX = point.x - this->figureInProgress->x;
		int offsetY = point.y - this->figureInProgress->y;
		/*this->figureInProgress->x = point.x;
		this->figureInProgress->y = point.y;*/

		auto pDoc = GetDocument();
		CFigure* r = pDoc->m_figures[this->m_dragNumber];
		r->x += offsetX;
		r->y += offsetY;

		/*pDoc->m_figures.SetAt(m_dragNumber, r);*/
		InvalidateRect(NULL);
	}

	CView::OnMouseMove(nFlags, point);
}

int CPaintMFCView::FindFigure(CPoint point) {
	auto pDoc = GetDocument();
	for (int i = (pDoc->m_figures.GetCount() - 1); i >= 0; i--) {
		if (pDoc->m_figures[i]->PtInFig(point.x, point.y)) {
			return i;
		}
	}

	return -1;
}

void CPaintMFCView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	auto pDoc = GetDocument();
	auto selected = this->FindFigure(point);
	if (m_selected == selected) {
		this->m_selected = -1;
	}
	else {
		this->m_selected = selected;
	}

	InvalidateRect(NULL);
	CView::OnRButtonDown(nFlags, point);
}


void CPaintMFCView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if ((this->m_selected > -1) && (nChar == VK_DELETE)) {
		auto pDoc = GetDocument();
		CFigure* fig = pDoc->m_figures[m_selected];
		pDoc->m_figures.RemoveAt(m_selected);
		pDoc->SetModifiedFlag();
		this->m_selected = -1;
		delete fig;
		Invalidate();
	}

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}
