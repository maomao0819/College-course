
// MFCApplication1.h: MFCApplication1 應用程式的主要標頭檔
//
#pragma once

#ifndef __AFXWIN_H__
	#error "對 PCH 包含此檔案前先包含 'stdafx.h'"
#endif

#include "resource.h"       // 主要符號


// CMFCApplication1App:
// 查看 MFCApplication1.cpp 以了解此類別的實作
//

class CMFCApplication1App : public CWinApp
{
public:
	CMFCApplication1App() noexcept;


// 覆寫
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 程式碼實作
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication1App theApp;
