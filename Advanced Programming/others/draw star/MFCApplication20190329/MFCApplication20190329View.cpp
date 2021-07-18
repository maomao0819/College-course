
// MFCApplication20190329View.cpp: CMFCApplication20190329View 類別的實作
//

#include "stdafx.h"
#include "math.h"

// SHARED_HANDLERS 可以定義在實作預覽、縮圖和搜尋篩選條件處理常式的
// ATL 專案中，並允許與該專案共用文件程式碼。
#ifndef SHARED_HANDLERS
#include "MFCApplication20190329.h"
#endif

#include "MFCApplication20190329Doc.h"
#include "MFCApplication20190329View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication20190329View

IMPLEMENT_DYNCREATE(CMFCApplication20190329View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication20190329View, CView)
	// 標準列印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMFCApplication20190329View 建構/解構

CMFCApplication20190329View::CMFCApplication20190329View() noexcept
{
	// TODO: 在此加入建構程式碼
	pt2.x = -1;

}

CMFCApplication20190329View::~CMFCApplication20190329View()
{
}

BOOL CMFCApplication20190329View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此經由修改 CREATESTRUCT cs 
	// 達到修改視窗類別或樣式的目的

	return CView::PreCreateWindow(cs);
}

// CMFCApplication20190329View 繪圖

void CMFCApplication20190329View::OnDraw(CDC* pDC)	//pDC = now_pen
{
	CMFCApplication20190329Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int cx = 200, cy = 200;
	int r = 100;
	const static double PI = 3.1415927;
	const static double val = PI / 180;
	CRect r1;	
	GetClientRect(&r1);	//r1 = window's client, Retrieves the coordinates of a window's client area.
	int H = r1.Height();
	int W = r1.Width();
	cx = W / 2;
	cy = H / 2;
	r = (W > H) ? H / 2 : W / 2;
	pDC->MoveTo(cx + r * cos(18 * val), cy - r * sin(18 * val));
	CPen red_pen, *old_pen;
	CBrush red_brush, *old_brush;
	red_pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	red_brush.CreateSolidBrush(RGB(255, 128, 128));
	old_pen = pDC->SelectObject(&red_pen);		//input new_pen and return old_pen
	old_brush = pDC->SelectObject(&red_brush);
	for (int i = 1; i <= 5; i++)
		pDC->LineTo(cx + r * cos((18 + 144 * i) * val), cy - r * sin((18 + 144 * i) * val));
	for (int i = 1; i <= 5; i++)
		pDC->FloodFill(cx + r / 2.0 * cos((18 + 144 * i) * val), cy - r / 2.0 * sin((18 + 144 * i) * val), RGB(255, 0, 0));
	pDC->SelectObject(old_pen);					//change pen to old_pen
	pDC->SelectObject(old_brush);
	if (pt2.x != -1)
	{
		pDC->MoveTo(pt1);
		pDC->LineTo(pt2);
	}
	// TODO: 在此加入原生資料的描繪程式碼
}


// CMFCApplication20190329View 列印

BOOL CMFCApplication20190329View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 預設的準備列印程式碼
	return DoPreparePrinting(pInfo);
}

void CMFCApplication20190329View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印前額外的初始設定
}

void CMFCApplication20190329View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印後的清除程式碼
}


// CMFCApplication20190329View 診斷

#ifdef _DEBUG
void CMFCApplication20190329View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication20190329View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication20190329Doc* CMFCApplication20190329View::GetDocument() const // 內嵌非偵錯版本
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication20190329Doc)));
	return (CMFCApplication20190329Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication20190329View 訊息處理常式


void CMFCApplication20190329View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	pt1 = point;
	pt2.x = -1;
	CView::OnLButtonDown(nFlags, point);
}


void CMFCApplication20190329View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	pt2 = point;
	Invalidate();	//do right now instead of doing when calling function OnDraw
	CView::OnLButtonUp(nFlags, point);
}
