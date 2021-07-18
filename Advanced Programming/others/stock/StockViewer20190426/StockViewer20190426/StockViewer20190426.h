
// StockViewer20190426.h: StockViewer20190426 應用程式的主要標頭檔
//
#pragma once

#ifndef __AFXWIN_H__
	#error "對 PCH 包含此檔案前先包含 'stdafx.h'"
#endif

#include "resource.h"       // 主要符號


// CStockViewer20190426App:
// 查看 StockViewer20190426.cpp 以了解此類別的實作
//

class CStockViewer20190426App : public CWinApp
{
public:
	CStockViewer20190426App() noexcept;


// 覆寫
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 程式碼實作
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CStockViewer20190426App theApp;
