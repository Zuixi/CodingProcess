
// MFCChapter2View.cpp : implementation of the CMFCChapter2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCChapter2.h"
#endif

#include "MFCChapter2Doc.h"
#include "MFCChapter2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCChapter2View

IMPLEMENT_DYNCREATE(CMFCChapter2View, CView)

BEGIN_MESSAGE_MAP(CMFCChapter2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCChapter2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CMFCChapter2View construction/destruction

const CRect CMFCChapter2View::m_rcSquares[9] = 
{
	CRect {16,16,112,112},
	CRect {128,16,224,112},
	CRect {240,16,336,112},

	CRect {16,128,112,224},
	CRect {128,128,224,224},
	CRect {240,128,336,224},

	CRect {16,240,112,336},
	CRect {128,240,224,336},
	CRect {240,240,336,336}
};

CMFCChapter2View::CMFCChapter2View() noexcept
{
	// TODO: add construction code here
	m_nNextChar = EX;
	::ZeroMemory(m_nGameGrid, 9 * sizeof(int));

	// Register a WNDCLASS
	/*
	CString strWndClass = AfxRegisterWndClass{
		CS_DBLCLKS,
		AfxGetApp()->LoadStandardCursor(IDC_ARROW),
		(HBRUSH)(COLOR_3DFACE + 1),    // Background brush

		AfxGetApp()->LoadStandardIcon(IDI_WINLOGO);    // class icon
	}
	*/
}

CMFCChapter2View::~CMFCChapter2View()
{
}

BOOL CMFCChapter2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CMFCChapter2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// do nothing if it is o return,if the click occured outside the 
	// tic-tac-toe grid, or if a nonempty suqare was clicked

	if (m_nNextChar != EX)
		return;

	int nPos = GetRectID(point);
	if ((nPos == 1) || (m_nGameGrid[nPos] != 0))
	{
		return;
	}

	// add an x to the game grid and toggle m_nNextChar
	m_nGameGrid[nPos] = EX;
	m_nNextChar = OH;

	// Draw an X on the screen and see if either player has own

	CClientDC dc(this);
	DrawX(&dc, nPos);
	CheckForGameOver();
}

void CMFCChapter2View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// do nothing if it is X return,if the click occured outsied the
	// tic-tac-toe grid, or if a nonemypt square was clicked

	if (m_nNextChar != OH)
		return;

	int nPos = GetRectID(point);
	if ((nPos == -1) || (m_nGameGrid[nPos] != 0))
	{
		return;
	}

	// add an O to the game grid and toggle m_nNextChar
	m_nGameGrid[nPos] = OH;
	m_nNextChar = EX;

	// Draw an X on the screen and see if either player has own

	CClientDC dc(this);
	DrawO(&dc, nPos);
	CheckForGameOver();

}

void CMFCChapter2View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// reset the game if one of the thick black lines defining the game
	// grid is double-clicked with the left mouse button
	CClientDC dc(this);
	if (dc.GetPixel(point) == RGB(0, 0, 0))
		ResetGame();
}

int CMFCChapter2View::GetRectID(CPoint point)
{
	// Hit-test each of the grids nine squares and return a rectangle ID
	// (0-8) if (point.x,point.y) lies inside a square

	for (int i = 0; i < 9; i++)
	{
		if (m_rcSquares[i].PtInRect(point))
			return i;
	}

	return -1;
}




// CMFCChapter2View drawing

void CMFCChapter2View::OnDraw(CDC* pDC)
{
	CMFCChapter2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	CPen pen(PS_SOLID, 16, RGB(0, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&pen);

	pDC->MoveTo(120, 16);
	pDC->LineTo(120, 336);

	pDC->MoveTo(232, 16);
	pDC->LineTo(232, 336);

	pDC->MoveTo(16, 120);
	pDC->LineTo(336, 120);

	pDC->MoveTo(16, 232);
	pDC->LineTo(336, 232);

	// draw the xs and os

	for (int i = 0; i < 9; i++)
	{
		if (m_nGameGrid[i]==EX)
		{
			// 
			DrawX(pDC, i);
		}
		else if (m_nGameGrid[i] == OH)
		{
			DrawO(pDC, i);
		}
	}

	pDC->SelectObject(pOldPen);
 } // CMFCChapter2View printing

void CMFCChapter2View::DrawO(CDC * pDC, int nPos)
{
	CPen pen(PS_SOLID, 16, RGB(0, 0, 255));
	CPen* pOldPen = pDC->SelectObject(&pen);

	pDC->SelectStockObject(NULL_BRUSH);

	CRect rect = m_rcSquares[nPos];
	rect.DeflateRect(16, 16);
	pDC->Ellipse(rect);

	pDC->SelectObject(pOldPen);

}

void CMFCChapter2View::DrawX(CDC* pDC, int nPos)
{
	CPen pen(PS_SOLID, 16, RGB(25, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&pen);

	CRect rect = m_rcSquares[nPos];
	rect.DeflateRect(16, 16);
	pDC->MoveTo(rect.left,rect.top);
	pDC->LineTo(rect.right, rect.bottom);
	pDC->MoveTo(rect.left, rect.bottom);
	pDC->LineTo(rect.right, rect.top);

	pDC->SelectObject(pOldPen);
}

void CMFCChapter2View::ResetGame()
{
	m_nNextChar = EX;
	::ZeroMemory(m_nGameGrid, 9 * sizeof(int));
	Invalidate();
}

BOOL CMFCChapter2View::IsDraw()
{
	for (int i = 0; i < 9; i++)
	{
		if (m_nGameGrid[i] == 0)
			return FALSE;
	}

	return TRUE;
}

int CMFCChapter2View::IsWinner()
{
	static int nPattern[8][3] =
	{
		0,1.2,
		3,4,5,
		6,7,8,
		0,3,6,
		1,4,7,
		2,5,8,
		0,4,8,
		2,4,6
	};

	for (int i = 0; i < 8; i++)
	{
		if ((m_nGameGrid[nPattern[i][0]] == EX) &&(m_nGameGrid[nPattern[i][1]] == EX) && (m_nGameGrid[nPattern[i][2]] == EX))
		{
			return EX;
		}

		if ((m_nGameGrid[nPattern[i][0]] == OH)&&  (m_nGameGrid[nPattern[i][1]] == OH) && (m_nGameGrid[nPattern[i][2]] == OH))
		{
			return OH;
		}
	}
}

void CMFCChapter2View::CheckForGameOver()
{
	int nWiner;

	// if the grid contains three sonsecutive xs or os,declare a winner
	// and start a new game

	if (nWiner = IsWinner())
	{
		CString string = (nWiner == EX) ? _T("X Wins!") : _T("O WIns!");
		MessageBox(string, _T("Game Over", MB_ICONEXCLAMATION | MB_OK));
		ResetGame();
	}
	else if (IsDraw())
	{
		MessageBox(_T("It is a draw"), _T("Game Over", MB_ICONEXCLAMATION | MB_OK));
		ResetGame();
	}
}
void CMFCChapter2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCChapter2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCChapter2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCChapter2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCChapter2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCChapter2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCChapter2View diagnostics

#ifdef _DEBUG
void CMFCChapter2View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCChapter2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCChapter2Doc* CMFCChapter2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCChapter2Doc)));
	return (CMFCChapter2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCChapter2View message handlers
