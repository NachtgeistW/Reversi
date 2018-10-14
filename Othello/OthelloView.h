
// OthelloView.h : COthelloView 类的接口
//

#pragma once
#include "OthelloDoc.h"
#include "CPlay.h"
#include "GUISetting.h"
#include "CGameDlg.h"

class COthelloView : public CView
{
protected: // 仅从序列化创建
	COthelloView();
	DECLARE_DYNCREATE(COthelloView)

// 特性
public:
	COthelloDoc* GetDocument() const;
	//#include "OthelloDoc.h" to fix error The identifier "Cothellodoc" is undefined
// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~COthelloView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void DrawChess(CPoint point, COLORREF color);
	void DrawChess(int xv, int yv, COLORREF color);
	void RefreshBoard();
	bool IsOutOfEdge(CPoint point);

	CPlay *play;
protected:
	COLORREF blackPen, whitePen;
	const static int boardEdgeLAT = 100,
		//the Right and Bottom edge of the chess board
		boardEdgeRAB = 900,
		//the Diameter of a chess
		chessDia = 90;

public:
	CRect getBoardSize();
	void RefreshChess();
	void ShowValid();
	void RefreshMain();
};

#ifndef _DEBUG  // OthelloView.cpp 中的调试版本
inline COthelloDoc* COthelloView::GetDocument() const
   { return reinterpret_cast<COthelloDoc*>(m_pDocument); }
#endif

