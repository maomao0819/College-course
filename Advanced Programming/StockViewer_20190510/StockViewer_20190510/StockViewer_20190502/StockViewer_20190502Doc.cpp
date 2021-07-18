
// StockViewer_20190502Doc.cpp: CStockViewer20190502Doc 類別的實作
//

#include "stdafx.h"
// SHARED_HANDLERS 可以定義在實作預覽、縮圖和搜尋篩選條件處理常式的
// ATL 專案中，並允許與該專案共用文件程式碼。
#ifndef SHARED_HANDLERS
#include "StockViewer_20190502.h"
#endif

#include "StockViewer_20190502Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CStockViewer20190502Doc

IMPLEMENT_DYNCREATE(CStockViewer20190502Doc, CDocument)

BEGIN_MESSAGE_MAP(CStockViewer20190502Doc, CDocument)
END_MESSAGE_MAP()


// CStockViewer20190502Doc 建構/解構

CStockViewer20190502Doc::CStockViewer20190502Doc() noexcept
{
	// TODO: 在此加入一次建構程式碼
	n = 0;
}

CStockViewer20190502Doc::~CStockViewer20190502Doc()
{
}

BOOL CStockViewer20190502Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此加入重新初始化程式碼
	// (SDI 文件會重用此文件)

	return TRUE;
}




// CStockViewer20190502Doc 序列化

void CStockViewer20190502Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此加入儲存程式碼
	}
	else
	{
		// TODO: 在此加入載入程式碼
		int i;
		CString fn = ar.GetFile()->GetFilePath();
		char *filename = new char[fn.GetLength() + 1];
		for (i = 0; i < fn.GetLength(); i++)
			filename[i] = fn[i];
		filename[i] = '\0';
		fn = ar.GetFile()->GetFileTitle();
		char *symbol = new char[fn.GetLength() + 1];
		for (i = 0; i < fn.GetLength(); i++)
			symbol[i] = fn[i];
		symbol[i] = '\0';
		stock.load(filename, symbol);
		n = stock.no-1;
	}
}

#ifdef SHARED_HANDLERS

// 縮圖的支援
void CStockViewer20190502Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改這段程式碼以繪製文件的資料
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜尋處理常式的支援
void CStockViewer20190502Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 設定來自文件資料的搜尋內容。
	// 內容部分應該以 ";" 隔開

	// 範例:     strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CStockViewer20190502Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CStockViewer20190502Doc 診斷

#ifdef _DEBUG
void CStockViewer20190502Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStockViewer20190502Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CStockViewer20190502Doc 命令
