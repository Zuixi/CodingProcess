
// MFCChapter2View.h : interface of the CMFCChapter2View class
//

#pragma once

#define EX 1
#define OH 2

class CMFCChapter2View : public CView
{
protected: // create from serialization only
	CMFCChapter2View() noexcept;
	DECLARE_DYNCREATE(CMFCChapter2View)

// Attributes
public:
	CMFCChapter2Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	static const CRect m_rcSquares[9];    // Grid coordinates
	int m_nGameGrid[9];    // Grid contens
	int m_nNextChar;    // Next character(EX or OH)
    
	int GetRectID(CPoint point);
	void DrawBoard(CDC * PDC);
	void DrawO(CDC* pDC, int nPos);
	void DrawX(CDC* pDC, int nPos);
	void ResetGame();
	void CheckForGameOver();
	int IsWinner();
	BOOL IsDraw();

// Implementation
public:
	virtual ~CMFCChapter2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFCChapter2View.cpp
inline CMFCChapter2Doc* CMFCChapter2View::GetDocument() const
   { return reinterpret_cast<CMFCChapter2Doc*>(m_pDocument); }
#endif

