
// HW1_0616098_黃秉茂View.h: CHW10616098黃秉茂View 類別的介面
//

#pragma once


class CHW10616098黃秉茂View : public CView
{
protected: // 僅從序列化建立
	CHW10616098黃秉茂View() noexcept;
	DECLARE_DYNCREATE(CHW10616098黃秉茂View)

// 屬性
public:
	CHW10616098黃秉茂Doc* GetDocument() const;

// 作業
public:
private:
	int num = 9;
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
	virtual ~CHW10616098黃秉茂View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // 對 HW1_0616098_黃秉茂View.cpp 中的版本進行偵錯
inline CHW10616098黃秉茂Doc* CHW10616098黃秉茂View::GetDocument() const
   { return reinterpret_cast<CHW10616098黃秉茂Doc*>(m_pDocument); }
#endif

