
// StockViewer20190426View.h: CStockViewer20190426View 類別的介面
//

#pragma once


class CStockViewer20190426View : public CView
{
protected: // 僅從序列化建立
	CStockViewer20190426View() noexcept;
	DECLARE_DYNCREATE(CStockViewer20190426View)

// 屬性
public:
	CStockViewer20190426Doc* GetDocument() const;

// 作業
public:

// 覆寫
public:
	virtual void OnDraw(CDC* pDC);  // 覆寫以描繪此檢視
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 程式碼實作
public:
	virtual ~CStockViewer20190426View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 對 StockViewer20190426View.cpp 中的版本進行偵錯
inline CStockViewer20190426Doc* CStockViewer20190426View::GetDocument() const
   { return reinterpret_cast<CStockViewer20190426Doc*>(m_pDocument); }
#endif

