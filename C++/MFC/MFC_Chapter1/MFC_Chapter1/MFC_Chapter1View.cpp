
// MFC_Chapter1View.cpp : implementation of the CMFCChapter1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFC_Chapter1.h"
#endif

#include "MFC_Chapter1Doc.h"
#include "MFC_Chapter1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCChapter1View

IMPLEMENT_DYNCREATE(CMFCChapter1View, CView)

BEGIN_MESSAGE_MAP(CMFCChapter1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCChapter1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCChapter1View construction/destruction

CMFCChapter1View::CMFCChapter1View() noexcept
{
	// TODO: add construction code here

}

CMFCChapter1View::~CMFCChapter1View()
{
}

BOOL CMFCChapter1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCChapter1View drawing

void CMFCChapter1View::OnDraw(CDC* /*pDC*/)
{
	CMFCChapter1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CRect rect;
	GetClientRect(&rect);

	CPaintDC dc(this);
	CPen pen;
	pen.CreateStockObject(NULL_PEN);
	dc.SelectObject(&pen);

	CBrush brush;
	brush.CreateStockObject(LTGRAY_BRUSH);
	dc.SelectObject(&brush);

	dc.Ellipse(0,0, 100, 100);
}


// CMFCChapter1View printing


void CMFCChapter1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCChapter1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCChapter1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCChapter1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCChapter1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCChapter1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCChapter1View diagnostics

#ifdef _DEBUG
void CMFCChapter1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCChapter1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCChapter1Doc* CMFCChapter1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCChapter1Doc)));
	return (CMFCChapter1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCChapter1View message handlers
