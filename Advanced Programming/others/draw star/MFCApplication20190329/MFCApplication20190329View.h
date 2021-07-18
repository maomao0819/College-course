
// MFCApplication20190329View.h: CMFCApplication20190329View 類別的介面
//

#pragma once


class CMFCApplication20190329View : public CView
{
protected: // 僅從序列化建立
	CMFCApplication20190329View() noexcept;
	DECLARE_DYNCREATE(CMFCApplication20190329View)

// 屬性
public:
	CMFCApplication20190329Doc* GetDocument() const;

// 作業
public:
private:
	CPoint pt1, pt2;

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
	virtual ~CMFCApplication20190329View();
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
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // 對 MFCApplication20190329View.cpp 中的版本進行偵錯
inline CMFCApplication20190329Doc* CMFCApplication20190329View::GetDocument() const
   { return reinterpret_cast<CMFCApplication20190329Doc*>(m_pDocument); }
#endif

