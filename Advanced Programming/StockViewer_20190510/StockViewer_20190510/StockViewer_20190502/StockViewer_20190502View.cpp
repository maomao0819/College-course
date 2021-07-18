
// StockViewer_20190502View.cpp: CStockViewer20190502View 類別的實作
//

#include "stdafx.h"
// SHARED_HANDLERS 可以定義在實作預覽、縮圖和搜尋篩選條件處理常式的
// ATL 專案中，並允許與該專案共用文件程式碼。
#ifndef SHARED_HANDLERS
#include "StockViewer_20190502.h"
#endif

#include "StockViewer_20190502Doc.h"
#include "StockViewer_20190502View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStockViewer20190502View

IMPLEMENT_DYNCREATE(CStockViewer20190502View, CView)

BEGIN_MESSAGE_MAP(CStockViewer20190502View, CView)
	// 標準列印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_Prev, &CStockViewer20190502View::OnPrev)
	ON_COMMAND(ID_Next, &CStockViewer20190502View::OnNext)
	ON_COMMAND(ID_First, &CStockViewer20190502View::OnFirst)
	ON_COMMAND(ID_Last, &CStockViewer20190502View::OnLast)
	ON_UPDATE_COMMAND_UI(ID_Prev, &CStockViewer20190502View::OnUpdatePrev)
	ON_UPDATE_COMMAND_UI(ID_Next, &CStockViewer20190502View::OnUpdateNext)
	ON_UPDATE_COMMAND_UI(ID_First, &CStockViewer20190502View::OnUpdateFirst)
	ON_UPDATE_COMMAND_UI(ID_Last, &CStockViewer20190502View::OnUpdateLast)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CStockViewer20190502View 建構/解構

CStockViewer20190502View::CStockViewer20190502View() noexcept
{
	// TODO: 在此加入建構程式碼
	pt1.x = -1;	//unuse
}

CStockViewer20190502View::~CStockViewer20190502View()
{
}

BOOL CStockViewer20190502View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此經由修改 CREATESTRUCT cs 
	// 達到修改視窗類別或樣式的目的

	return CView::PreCreateWindow(cs);
}

// CStockViewer20190502View 繪圖

void CStockViewer20190502View::OnDraw(CDC* pDC)
{
	CStockViewer20190502Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rect;
	GetClientRect(rect);
	int H = rect.Height();
	int W = rect.Width();
	//https://blog.csdn.net/longzaitianya1989/article/details/18266899
	/*CDC MemDC; //首先定义一个显示设备对象
	CBitmap MemBitmap;//定义一个位图对象
	//随后建立与屏幕显示兼容的内存显示设备 
	MemDC.CreateCompatibleDC(NULL);
	//这时还不能绘图，因为没有地方画 ^_^ 
	//下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小 
	MemBitmap.CreateCompatibleBitmap(pDC, W, H);
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);
	MemDC.FillSolidRect(0, 0, W, H, RGB(255, 255, 255));
	pDoc->stock.draw(&MemDC, H, W, pDoc->n, pt2.x);
	if (pt1.x == -1 && pt2.y >= 20 && pt2.y <= 3*H/4)
	{
		MemDC.MoveTo(0, pt2.y);
		MemDC.LineTo(W, pt2.y);
		MemDC.MoveTo(pt2.x, 20);
		MemDC.LineTo(pt2.x, 3*H/4);
	}
	//将内存中的图拷贝到屏幕上进行显示 
	pDC->BitBlt(0, 0, W, H, &MemDC, 0, 0, SRCCOPY);
	//绘图完成后的清理 
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();*/
	int *x_line = new int;
	*x_line = pt2.x;
	int *y_line_A = new int;
	*y_line_A = pt2.y;
	int *y_line_V = new int;
	*y_line_V = 0;
	pDoc->stock.draw(pDC, H, W, pDoc->n, pt2.x, x_line, y_line_A, y_line_V);
	if (pt1.x == -1 && (pt2.y >= H / 8 && pt2.y <= 3 * H / 4) || (pt2.y > H * 4 / 5 && pt2.y < H * 39 / 40))
	{
		pDC->MoveTo(0, *y_line_A);
		pDC->LineTo(W, *y_line_A);
		pDC->MoveTo(*x_line, H / 8);
		pDC->LineTo(*x_line, 3 * H / 4);
		if (*y_line_V)
		{
			pDC->MoveTo(0, *y_line_V);
			pDC->LineTo(W, *y_line_V);
		}
	}
}


// CStockViewer20190502View 列印

BOOL CStockViewer20190502View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 預設的準備列印程式碼
	return DoPreparePrinting(pInfo);
}

void CStockViewer20190502View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印前額外的初始設定
}

void CStockViewer20190502View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印後的清除程式碼
}


// CStockViewer20190502View 診斷

#ifdef _DEBUG
void CStockViewer20190502View::AssertValid() const
{
	CView::AssertValid();
}

void CStockViewer20190502View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStockViewer20190502Doc* CStockViewer20190502View::GetDocument() const // 內嵌非偵錯版本
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStockViewer20190502Doc)));
	return (CStockViewer20190502Doc*)m_pDocument;
}
#endif //_DEBUG


// CStockViewer20190502View 訊息處理常式


void CStockViewer20190502View::OnPrev()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CStockViewer20190502Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->n--;
	Invalidate();
}


void CStockViewer20190502View::OnNext()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CStockViewer20190502Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->n++;
	Invalidate();
}


void CStockViewer20190502View::OnFirst()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CStockViewer20190502Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rect;
	GetClientRect(rect);
	int W = rect.Width();
	pDoc->n = W/10 - 1;
	Invalidate();
}


void CStockViewer20190502View::OnLast()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CStockViewer20190502Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->n = pDoc->stock.no-1;
	Invalidate();
}


void CStockViewer20190502View::OnUpdatePrev(CCmdUI *pCmdUI)
{
	// TODO: 在此加入您的命令更新 UI 處理常式程式碼
	CStockViewer20190502Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rect;
	GetClientRect(rect);
	int W = rect.Width();
	pCmdUI->Enable(pDoc->n!= W/10-1);
}


void CStockViewer20190502View::OnUpdateNext(CCmdUI *pCmdUI)
{
	// TODO: 在此加入您的命令更新 UI 處理常式程式碼
	CStockViewer20190502Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pCmdUI->Enable(pDoc->n != pDoc->stock.no-1);
}


void CStockViewer20190502View::OnUpdateFirst(CCmdUI *pCmdUI)
{
	// TODO: 在此加入您的命令更新 UI 處理常式程式碼
	CStockViewer20190502Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rect;
	GetClientRect(rect);
	int W = rect.Width();
	pCmdUI->Enable(pDoc->n != W / 10 - 1);
}


void CStockViewer20190502View::OnUpdateLast(CCmdUI *pCmdUI)
{
	// TODO: 在此加入您的命令更新 UI 處理常式程式碼
	CStockViewer20190502Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pCmdUI->Enable(pDoc->n != pDoc->stock.no - 1);
}


void CStockViewer20190502View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	pt1 = point;
	CView::OnLButtonDown(nFlags, point);
}


void CStockViewer20190502View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	CStockViewer20190502Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	/*pDoc->n -= ((point.x - pt1.x) / 10);
	CRect rect;
	GetClientRect(rect);
	int W = rect.Width();
	if(pDoc->n < W / 10 - 1)
		pDoc->n = W / 10 - 1;
	if (pDoc->n > pDoc->stock.no - 1)
		pDoc->n = pDoc->stock.no - 1;*/
	pt1.x = -1;
	Invalidate();
	CView::OnLButtonUp(nFlags, point);
}


void CStockViewer20190502View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	if (pt1.x == -1)
	{
		//畫十字
		pt2 = point;
		//Invalidate();
		RedrawWindow();
	}
	else
	{
		CStockViewer20190502Doc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		pDoc->n -= ((point.x - pt1.x) / 10);
		CRect rect;
		GetClientRect(rect);
		int W = rect.Width();
		if (pDoc->n < W / 10 - 1)
			pDoc->n = W / 10 - 1;
		if (pDoc->n > pDoc->stock.no - 1)
			pDoc->n = pDoc->stock.no - 1;
		pt1 = point;
		Invalidate();
	}

	CView::OnMouseMove(nFlags, point);
}


BOOL CStockViewer20190502View::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	
	CStockViewer20190502Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return CView::OnMouseWheel(nFlags, zDelta, pt);;
	int disp = 1;
	if (nFlags == MK_CONTROL)
		disp = 5;
	else if (nFlags == MK_SHIFT)
		disp = 10;
	if (zDelta > 0)
	{
		pDoc->n -= disp;
		CRect rect;
		GetClientRect(rect);
		int W = rect.Width();
		if (pDoc->n < W / 10 - 1)
			pDoc->n = W / 10 - 1;
	}
		
	else if (zDelta < 0)
	{
		pDoc->n += disp;
		if (pDoc->n > pDoc->stock.no - 1)
			pDoc->n = pDoc->stock.no - 1;
	}	
	Invalidate();
	return CView::OnMouseWheel(nFlags, zDelta, pt);
	//	Reference: 
	//	https://blog.csdn.net/chunyexiyu/article/details/9075311
}
