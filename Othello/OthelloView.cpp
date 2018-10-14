
// OthelloView.cpp : COthelloView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Othello.h"
#endif

#include "OthelloDoc.h"
#include "OthelloView.h"

#include "GUISetting.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COthelloView

IMPLEMENT_DYNCREATE(COthelloView, CView)

BEGIN_MESSAGE_MAP(COthelloView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COthelloView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// COthelloView 构造/析构

COthelloView::COthelloView()
{
	blackPen = RGB(0, 0, 0);
	whitePen = RGB(255, 255, 255);
	play = new CPlay;
}

COthelloView::~COthelloView()
{
	delete play;
}

BOOL COthelloView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// COthelloView 绘制

void COthelloView::OnDraw(CDC* pDC)
{
	COthelloDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	RefreshMain();
	SetStatusBar(play->CountChessNum(play->black), play->CountChessNum(play->white), play->GetPlayer());
	CPoint point = GetCursorPos(&point);
	OnLButtonDown(MK_LBUTTON, point);
}

// COthelloView 打印

void COthelloView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COthelloView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void COthelloView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void COthelloView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void COthelloView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COthelloView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COthelloView 诊断

#ifdef _DEBUG
void COthelloView::AssertValid() const
{
	CView::AssertValid();
}

void COthelloView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COthelloDoc* COthelloView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COthelloDoc)));
	return (COthelloDoc*)m_pDocument;
}
#endif //_DEBUG


// COthelloView 消息处理程序

void COthelloView::RefreshMain()
{
	RefreshBoard();
	RefreshChess();
	ShowValid();
	SetStatusBar(play->CountChessNum(play->black), play->CountChessNum(play->white), play->GetPlayer());
}

//using this function to draw chess board
void COthelloView::RefreshBoard()
{
	CDC * pDC = GetDC();
	//draw board
	CBrush boardBrush = (HS_FDIAGONAL, RGB(0, 86, 31));
	pDC->SelectObject(&boardBrush);
	for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++)
			pDC->Rectangle(i * 100, j * 100, i * 100 + 100, j * 100 + 100);
	//draw the text of row and column
	CString str;
	char cr = 'A';
	for (int i = 1; i <= 8; i++)
	{
		CRect rct(100, 0, i * 200, 100);
		CRect rcb(100, 1800, i * 200, 100);
		CRect rcl(0, i * 100, 100, i * 100 + 100);
		CRect rcr(1800, i * 100, 100, i * 100 + 100);
		//draw the num in row
		str.Format("%c", cr + i - 1);
		pDC->DrawText(str, rct, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//水平、垂直居中
		pDC->DrawText(str, rcb, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//draw the num in column
		str.Format("%d", i);
		pDC->DrawText(str, rcl, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		pDC->DrawText(str, rcr, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}

//using this function to draw chess
void COthelloView::RefreshChess()
{
	// TODO: 在此处添加实现代码.
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			if (play->GetChessColor(i, j) == play->black)
				DrawChess(j * 100, i * 100, blackPen);
			else if (play->GetChessColor(i, j) == play->white)
				DrawChess(j * 100, i * 100, whitePen);
		}
	}

}

void COthelloView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CView::OnLButtonDown(nFlags, point);
	if (!IsOutOfEdge(point))
	{
		play->GameMain(point);
		RefreshMain();
	}
}

//using this function to draw the valid place
void COthelloView::ShowValid()
{
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
			if (play->GlobalReversiCheck(i, j, play->GetPlayer()) && play->IsAdjChessDif(i, j) && 
				play->GetChessColor(i, j) == play->empty)
			{
				CDC * pDC = GetDC();
				CBrush blackValidPointBrush(RGB(126, 206, 244));
				CBrush whiteValidPointBrush(RGB(255, 219, 73));
				if(play->GetPlayer() == play->black)
					pDC->SelectObject(blackValidPointBrush);
				else if (play->GetPlayer() == play->white)
					pDC->SelectObject(whiteValidPointBrush);
				pDC->Ellipse(j * 100 + 10, i * 100 + 10, j * 100 + 90, i * 100 + 90);
				ReleaseDC(pDC);
			}
	}
}


bool COthelloView::IsOutOfEdge(CPoint point)
{
	// TODO: 在此处添加实现代码.
	if (point.x < boardEdgeLAT || point.x > boardEdgeRAB ||
		point.y < boardEdgeLAT || point.y > boardEdgeRAB)
		return true;
	else
		return false;
}

void COthelloView::DrawChess(CPoint point, COLORREF color)
{
	CDC * pDC = GetDC();
	CBrush chessBrush = (HS_FDIAGONAL, color);
	pDC->SelectObject(&chessBrush);
	pDC->Ellipse(point.x + 10, point.y + 10, point.x + chessDia, point.y + chessDia);
	ReleaseDC(pDC);
}

void COthelloView::DrawChess(int xv, int yv, COLORREF color)
{
	CDC * pDC = GetDC();
	CBrush chessBrush = (HS_FDIAGONAL, color);
	pDC->SelectObject(&chessBrush);
	pDC->Ellipse(xv + 10, yv + 10, xv + chessDia, yv + chessDia);
}

CRect COthelloView::getBoardSize()
{
	return CRect(boardEdgeLAT, boardEdgeLAT, boardEdgeRAB, boardEdgeRAB);
}
