
// HW1_0616098_黃秉茂.h: HW1_0616098_黃秉茂 應用程式的主要標頭檔
//
#pragma once

#ifndef __AFXWIN_H__
	#error "對 PCH 包含此檔案前先包含 'stdafx.h'"
#endif

#include "resource.h"       // 主要符號


// CHW10616098黃秉茂App:
// 查看 HW1_0616098_黃秉茂.cpp 以了解此類別的實作
//

class CHW10616098黃秉茂App : public CWinApp
{
public:
	CHW10616098黃秉茂App() noexcept;


// 覆寫
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 程式碼實作
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CHW10616098黃秉茂App theApp;
