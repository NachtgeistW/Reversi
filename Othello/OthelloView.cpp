
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
	DrawBoard(pDC);

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

//using this function to draw chess board
void COthelloView::DrawBoard(CDC *pDC)
{
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
	//draw the 4 chess had played at the beginning of the game
	DrawChess(400, 400, whitePen);
	DrawChess(500, 500, whitePen);
	DrawChess(400, 500, blackPen);
	DrawChess(500, 400, blackPen);

}

void COthelloView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CView::OnLButtonDown(nFlags, point);
	if (!IsOutOfEdge(point) && !play->IsInvalidPlay(point))
	{
		CPoint location = play->CalChessPoint(point);
		if (play->GetRound() % 2 == 0)
			DrawChess(location, blackPen);
		else
			DrawChess(location, whitePen);
		play->IncRound();
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
}

void COthelloView::DrawChess(int x, int y, COLORREF color)
{
	CDC * pDC = GetDC();
	CBrush chessBrush = (HS_FDIAGONAL, color);
	pDC->SelectObject(&chessBrush);
	pDC->Ellipse(x + 10, y + 10, x + chessDia, y + chessDia);
}

CRect COthelloView::getBoardSize()
{
	return CRect(boardEdgeLAT, boardEdgeLAT, boardEdgeRAB, boardEdgeRAB);
}
