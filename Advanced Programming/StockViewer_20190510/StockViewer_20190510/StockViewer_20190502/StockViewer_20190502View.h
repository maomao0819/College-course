
// StockViewer_20190502View.h: CStockViewer20190502View 類別的介面
//

#pragma once


class CStockViewer20190502View : public CView
{
protected: // 僅從序列化建立
	CStockViewer20190502View() noexcept;
	DECLARE_DYNCREATE(CStockViewer20190502View)

// 屬性
public:
	CStockViewer20190502Doc* GetDocument() const;
	CPoint pt1;
	CPoint pt2;
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
	virtual ~CStockViewer20190502View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPrev();
	afx_msg void OnNext();
	afx_msg void OnFirst();
	afx_msg void OnLast();
	afx_msg void OnUpdatePrev(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNext(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFirst(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLast(CCmdUI *pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // 對 StockViewer_20190502View.cpp 中的版本進行偵錯
inline CStockViewer20190502Doc* CStockViewer20190502View::GetDocument() const
   { return reinterpret_cast<CStockViewer20190502Doc*>(m_pDocument); }
#endif

