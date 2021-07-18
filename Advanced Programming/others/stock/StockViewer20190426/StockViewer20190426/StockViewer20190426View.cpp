
// StockViewer20190426View.cpp: CStockViewer20190426View 類別的實作
//

#include "stdafx.h"
// SHARED_HANDLERS 可以定義在實作預覽、縮圖和搜尋篩選條件處理常式的
// ATL 專案中，並允許與該專案共用文件程式碼。
#ifndef SHARED_HANDLERS
#include "StockViewer20190426.h"
#endif

#include "StockViewer20190426Doc.h"
#include "StockViewer20190426View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStockViewer20190426View

IMPLEMENT_DYNCREATE(CStockViewer20190426View, CView)

BEGIN_MESSAGE_MAP(CStockViewer20190426View, CView)
	// 標準列印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CStockViewer20190426View 建構/解構

CStockViewer20190426View::CStockViewer20190426View() noexcept
{
	// TODO: 在此加入建構程式碼

}

CStockViewer20190426View::~CStockViewer20190426View()
{
}

BOOL CStockViewer20190426View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此經由修改 CREATESTRUCT cs 
	// 達到修改視窗類別或樣式的目的

	return CView::PreCreateWindow(cs);
}

// CStockViewer20190426View 繪圖

void CStockViewer20190426View::OnDraw(CDC* /*pDC*/)
{
	CStockViewer20190426Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此加入原生資料的描繪程式碼
}


// CStockViewer20190426View 列印

BOOL CStockViewer20190426View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 預設的準備列印程式碼
	return DoPreparePrinting(pInfo);
}

void CStockViewer20190426View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印前額外的初始設定
}

void CStockViewer20190426View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印後的清除程式碼
}


// CStockViewer20190426View 診斷

#ifdef _DEBUG
void CStockViewer20190426View::AssertValid() const
{
	CView::AssertValid();
}

void CStockViewer20190426View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStockViewer20190426Doc* CStockViewer20190426View::GetDocument() const // 內嵌非偵錯版本
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStockViewer20190426Doc)));
	return (CStockViewer20190426Doc*)m_pDocument;
}
#endif //_DEBUG


// CStockViewer20190426View 訊息處理常式
