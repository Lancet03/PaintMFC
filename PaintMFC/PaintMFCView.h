
// PaintMFCView.h : interface of the CPaintMFCView class
//

#pragma once


class CPaintMFCView : public CView
{
protected: // create from serialization only
	CPaintMFCView() noexcept;
	DECLARE_DYNCREATE(CPaintMFCView)

// Attributes
public:
	CPaintMFCDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CPaintMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int FindFigure(CPoint point);
	int m_dragNumber = -1;
	int m_selected = -1;
	CRectangle rectInProgress;
	BOOL m_bDrawInProgress = FALSE;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in PaintMFCView.cpp
inline CPaintMFCDoc* CPaintMFCView::GetDocument() const
   { return reinterpret_cast<CPaintMFCDoc*>(m_pDocument); }
#endif

