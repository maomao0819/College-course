
// HW1_0616098_黃秉茂View.cpp: CHW10616098黃秉茂View 類別的實作
//

#include "stdafx.h"
#include "math.h"
// SHARED_HANDLERS 可以定義在實作預覽、縮圖和搜尋篩選條件處理常式的
// ATL 專案中，並允許與該專案共用文件程式碼。
#ifndef SHARED_HANDLERS
#include "HW1_0616098_黃秉茂.h"
#endif

#include "HW1_0616098_黃秉茂Doc.h"
#include "HW1_0616098_黃秉茂View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHW10616098黃秉茂View

IMPLEMENT_DYNCREATE(CHW10616098黃秉茂View, CView)

BEGIN_MESSAGE_MAP(CHW10616098黃秉茂View, CView)
	// 標準列印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CHW10616098黃秉茂View 建構/解構

CHW10616098黃秉茂View::CHW10616098黃秉茂View() noexcept
{
	// TODO: 在此加入建構程式碼

}

CHW10616098黃秉茂View::~CHW10616098黃秉茂View()
{
}

BOOL CHW10616098黃秉茂View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此經由修改 CREATESTRUCT cs 
	// 達到修改視窗類別或樣式的目的

	return CView::PreCreateWindow(cs);
}

// CHW10616098黃秉茂View 繪圖

void CHW10616098黃秉茂View::OnDraw(CDC* pDC)
{
	CHW10616098黃秉茂Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	// get the window's size 
	CRect r1;
	GetClientRect(&r1);	//r1 = window's client, Retrieves the coordinates of a window's client area.
	int W = r1.Width();
	int H = r1.Height();
	//	ROC
	if (num % 3 == 0)
	{
		int unit = H / 2 > W / 3 ? W / 3 : H / 2;
		int w = 3 * unit;
		int h = 2 * unit;
		// the red part
		pDC->MoveTo(0, 0);
		CPen red_pen, *old_pen;
		CBrush red_brush, *old_brush;
		red_pen.CreatePen(PS_SOLID, 1, RGB(254, 0, 0));
		red_brush.CreateSolidBrush(RGB(254, 0, 0));
		old_pen = pDC->SelectObject(&red_pen);		//input new_pen and return old_pen
		old_brush = pDC->SelectObject(&red_brush);
		pDC->LineTo(0, h);
		pDC->LineTo(w, h);
		pDC->LineTo(w, 0);
		pDC->LineTo(0, 0);
		pDC->FloodFill(1, 1, RGB(254, 0, 0));
		// the blue part
		CPen blue_pen;
		CBrush blue_brush;
		blue_pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 149));
		blue_brush.CreateSolidBrush(RGB(0, 0, 149));
		pDC->SelectObject(&blue_pen);
		CPoint pt_bl_rec(0, 0);
		CSize sz_bl_rec(w / 2, h / 2);
		CRect blueRect(pt_bl_rec, sz_bl_rec);
		pDC->Rectangle(blueRect);
		pDC->FillRect(&blueRect, &blue_brush);
		// draw the white part
		CPen white_pen;
		CBrush white_brush;
		white_pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		white_brush.CreateSolidBrush(RGB(255, 255, 255));
		pDC->SelectObject(&white_pen);
		pDC->SelectObject(&white_brush);
		double cx = w / 2 / 2;
		double cy = h / 2 / 2;
		double wh_r = cx * 2 / 8;
		//		12 white rays 
		pDC->MoveTo(cx, cy - 2 * wh_r);
		const static double PI = 3.1415927;
		const static double val = PI / 180;
		int angle = 180 - 360 / 12 / 2 * 2;
		for (int i = 0; i < 12; i++)	//angle + 90 - 180 = 60
			pDC->LineTo(cx - 2 * wh_r * cos((angle * i + 60) * val), cy + 2 * wh_r * sin((angle * i + 60) * val));
		for (int i = 0; i < 12; i++)
			pDC->FloodFill(cx - wh_r * cos((angle * i + 60) * val), cy + wh_r * sin((angle * i + 60) * val), RGB(255, 255, 255));
		//		blue circle
		pDC->SelectObject(&blue_pen);
		pDC->SelectObject(&blue_brush);
		double bl_r = wh_r / 15 * 17;
		pDC->Ellipse(cx - bl_r, cy - bl_r, cx + bl_r, cy + bl_r);
		pDC->FloodFill(cx, cy, RGB(0, 0, 149));
		//		white circle
		pDC->SelectObject(&white_pen);
		pDC->SelectObject(&white_brush);
		pDC->Ellipse(cx - wh_r, cy - wh_r, cx + wh_r, cy + wh_r);
		pDC->FloodFill(cx, cy, RGB(255, 255, 255));
		pDC->SelectObject(old_pen);		
		pDC->SelectObject(old_brush);
	}
	//	Republic of Azerbaijan
	else if (num % 3 == 1)
	{
		int unit = H > W / 2 ? W / 2 : H;
		int w = 2 * unit;
		int h = unit;
		//	blue rectangular
		CPen blue_pen, *old_pen;
		CBrush blue_brush, *old_brush;
		blue_pen.CreatePen(PS_SOLID, 1, RGB(0, 151, 195));
		blue_brush.CreateSolidBrush(RGB(0, 151, 195));
		old_pen = pDC->SelectObject(&blue_pen);		//input new_pen and return old_pen
		old_brush = pDC->SelectObject(&blue_brush);
		CPoint pt_bl_rec(0, 0);
		CSize sz_rec(w, h / 3);
		CRect blueRect(pt_bl_rec, sz_rec);
		pDC->Rectangle(blueRect);
		pDC->FillRect(&blueRect, &blue_brush);
		//	red rectangular
		CPen red_pen;
		CBrush red_brush;
		red_pen.CreatePen(PS_SOLID, 1, RGB(224, 0, 52));
		red_brush.CreateSolidBrush(RGB(224, 0, 52));
		CPoint pt_re_rec(0, h / 3);
		CRect redRect(pt_re_rec, sz_rec);
		pDC->Rectangle(redRect);
		pDC->FillRect(&redRect, &red_brush);
		//	green rectangular
		CPen green_pen;
		CBrush green_brush;
		green_pen.CreatePen(PS_SOLID, 1, RGB(0, 174, 101));
		green_brush.CreateSolidBrush(RGB(0, 174, 101));
		CPoint pt_gr_rec(0, h * 2 / 3);
		CRect greenRect(pt_gr_rec, sz_rec);
		pDC->Rectangle(greenRect);
		pDC->FillRect(&greenRect, &green_brush);
		double w_cx = w / 2;
		double cy = h / 2;
		double w_r = h * 3 / 10 / 2;
		//	white circle
		CPen white_pen;
		CBrush white_brush;
		white_pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		white_brush.CreateSolidBrush(RGB(255, 255, 255));
		pDC->SelectObject(&white_pen);
		pDC->SelectObject(&white_brush);
		pDC->Ellipse(w_cx - w_r, cy - w_r, w_cx + w_r, cy + w_r);
		pDC->FloodFill(w_cx, cy, RGB(255, 255, 255));
		//	red circle
		double r_cx = w / 2 + h / 30;
		double r_r = h / 4 / 2;
		pDC->SelectObject(&red_pen);
		pDC->SelectObject(&red_brush);
		pDC->Ellipse(r_cx - r_r, cy - r_r, r_cx + r_r, cy + r_r);
		pDC->FloodFill(r_cx, cy, RGB(224, 0, 52));
		//	white star
		pDC->SelectObject(&white_pen);
		pDC->SelectObject(&white_brush);
		double sm_w_r = h / 6 / 2;
		double sm_w_cx = w_cx - w_r + 2 * h / 5 - sm_w_r;
		pDC->MoveTo(sm_w_cx, cy - sm_w_r);
		const static double PI = 3.1415927;
		const static double val = PI / 180;
		int angle = 180 - 360 / 8 / 2 * 2;
		for (int i = 0; i < 8; i++)	//angle + 90 - 180 = 45
			pDC->LineTo(sm_w_cx - sm_w_r * cos((angle * i + 45) * val), cy + sm_w_r * sin((angle * i + 45) * val));
		for (int i = 0; i < 8; i++)
		{ 
			pDC->FloodFill(sm_w_cx - sm_w_r / 2 * cos((angle * i + 45) * val), cy + sm_w_r / 2 * sin((angle * i + 45) * val), RGB(255, 255, 255));
			pDC->FloodFill(sm_w_cx - sm_w_r * 8 / 21 * cos((angle * i + 45 - 27) * val), cy + sm_w_r * 8 / 21 * sin((angle * i + 45 - 27) * val), RGB(255, 255, 255));
			pDC->FloodFill(sm_w_cx - sm_w_r * 8 / 19 * cos((angle * i + 45 - 27) * val), cy + sm_w_r * 8 / 19 * sin((angle * i + 45 - 27) * val), RGB(255, 255, 255));
		}
		pDC->FloodFill(sm_w_cx, cy, RGB(255, 255, 255));
		pDC->SelectObject(old_pen);
		pDC->SelectObject(old_brush);
	}
	//	Korea
	else if (num % 3 == 2)
	{
		int unit = H / 2 > W / 3 ? W / 3 : H / 2;
		int w = 3 * unit;
		int h = 2 * unit;
		//	boundary
		pDC->MoveTo(0, 0);
		pDC->LineTo(0, h);
		pDC->LineTo(w, h);
		pDC->LineTo(w, 0);
		pDC->LineTo(0, 0);
		// the red big circle
		CPen red_pen, *old_pen;
		CBrush red_brush, *old_brush;
		red_pen.CreatePen(PS_SOLID, 1, RGB(205, 46, 58));
		red_brush.CreateSolidBrush(RGB(205, 046, 58));
		old_pen = pDC->SelectObject(&red_pen);		//input new_pen and return old_pen
		old_brush = pDC->SelectObject(&red_brush);
		double cx = w / 2;
		double cy = h / 2;
		double r = cy / 2;
		pDC->Ellipse(cx - r, cy - r, cx + r, cy + r);
		//	the blue half circle
		CPen blue_pen;
		CBrush blue_brush;
		blue_pen.CreatePen(PS_SOLID, 1, RGB(0, 71, 160));
		blue_brush.CreateSolidBrush(RGB(0, 71, 160));
		pDC->SelectObject(&blue_pen);
		pDC->SelectObject(&blue_brush);
		double x_ratio = 3 / sqrt(13);
		double y_ratio = 2 / sqrt(13);
		CPoint half_cir_star(cx - r * x_ratio, cy - r * y_ratio);
		CPoint half_cir_end(cx + r * x_ratio, cy + r * y_ratio);
		CPoint big_cir_rec_star(cx - r, cy - r);
		CSize sz_big_cir_rec(2 * r, 2 * r);
		CRect big_cir_Rect(big_cir_rec_star, sz_big_cir_rec);
		pDC->Pie(big_cir_Rect, half_cir_star, half_cir_end);
		//	blue small circle
		double sm_r = r / 2;
		double b_cx = cx + sm_r * x_ratio;
		double b_cy = cy + sm_r * y_ratio;
		pDC->Ellipse(b_cx - sm_r, b_cy - sm_r, b_cx + sm_r, b_cy + sm_r);
		//	red small circle
		pDC->SelectObject(&red_pen);		
		pDC->SelectObject(&red_brush);
		double r_cx = cx - sm_r * x_ratio;
		double r_cy = cy - sm_r * y_ratio;
		pDC->Ellipse(r_cx - sm_r, r_cy - sm_r, r_cx + sm_r, r_cy + sm_r);
		//	the black bricks
		double bl_brick_h = h * 1 / 12 / 2;
		double bl_brick_w = h * 1 / 2 / 2;
		double half_of_bl_brick_w_x = bl_brick_w / 2 * y_ratio;
		double half_of_bl_brick_w_y = bl_brick_w / 2 * x_ratio;
		CPen black_pen;
		CBrush black_brush;
		black_pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		black_brush.CreateSolidBrush(RGB(0, 0, 0));
		pDC->SelectObject(&black_pen);
		pDC->SelectObject(&black_brush);
		double l_x = -1 * half_of_bl_brick_w_x;
		double l_y = half_of_bl_brick_w_y;
		double r_x = half_of_bl_brick_w_x;
		double r_y = -1 * half_of_bl_brick_w_y;
		double temp_rec_cx = 0;
		double temp_rec_cy = 0;
		double temp_rec_x[2];
		double temp_rec_y[2];
		double brick_dist = bl_brick_h * 3 / 2;
		double temp_rec_cx_it = brick_dist * x_ratio;
		double temp_rec_cy_it = brick_dist * y_ratio;
		int mark = 1;
		int time = 0;
		for (int i = 0; i < 4; i++)
		{
			switch (i)
			{
				case 0:		// left-upper
					temp_rec_cx = cx - (r + h * 1 / 4 / 2 + bl_brick_h / 2) * x_ratio;
					temp_rec_cy = cy - (r + h * 1 / 4 / 2 + bl_brick_h / 2) * y_ratio;
					temp_rec_cx_it *= -1;	// -
					temp_rec_cy_it *= -1;	// -
					break;
				case 1:		// right-lower
					temp_rec_cx = cx + (r + h * 1 / 4 / 2 + bl_brick_h / 2) * x_ratio;
					temp_rec_cy = cy + (r + h * 1 / 4 / 2 + bl_brick_h / 2) * y_ratio;
					temp_rec_cx_it *= -1;	// +
					temp_rec_cy_it *= -1;	// +
					break;
				case 2:		// left-lower
					temp_rec_cx = cx - (r + h * 1 / 4 / 2 + bl_brick_h / 2) * x_ratio;
					temp_rec_cy = cy + (r + h * 1 / 4 / 2 + bl_brick_h / 2) * y_ratio;
					temp_rec_cx_it *= -1;	// -
											// +
					l_y *= -1;
					r_y *= -1;
					mark = -1;
					break;
				case 3:		// right-upper
					temp_rec_cx = cx + (r + h * 1 / 4 / 2 + bl_brick_h / 2) * x_ratio;
					temp_rec_cy = cy - (r + h * 1 / 4 / 2 + bl_brick_h / 2) * y_ratio;
					temp_rec_cx_it *= -1;	// +
					temp_rec_cy_it *= -1;	// -
					break;
			}
			time = 3;
			while(time--)		// three blocks
			{
				temp_rec_x[0] = temp_rec_cx + bl_brick_h / 2 * x_ratio;
				temp_rec_x[1] = temp_rec_cx - bl_brick_h / 2 * x_ratio;
				temp_rec_y[0] = temp_rec_cy + bl_brick_h / 2 * y_ratio * mark;
				temp_rec_y[1] = temp_rec_cy - bl_brick_h / 2 * y_ratio * mark;
				pDC->MoveTo(temp_rec_x[0] + l_x, temp_rec_y[0] + l_y);
				pDC->LineTo(temp_rec_x[0] + r_x, temp_rec_y[0] + r_y);
				pDC->LineTo(temp_rec_x[1] + r_x, temp_rec_y[1] + r_y);
				pDC->LineTo(temp_rec_x[1] + l_x, temp_rec_y[1] + l_y);
				pDC->LineTo(temp_rec_x[0] + l_x, temp_rec_y[0] + l_y);
				pDC->FloodFill(temp_rec_cx, temp_rec_cy, RGB(0, 0, 0));
				temp_rec_cx += temp_rec_cx_it;
				temp_rec_cy += temp_rec_cy_it;
			}
		}
		//	the white bricks
		CPen white_pen;
		CBrush white_brush;
		white_pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		white_brush.CreateSolidBrush(RGB(255, 255, 255));
		pDC->SelectObject(&white_pen);
		pDC->SelectObject(&white_brush);
		//		right-lower
								// +
		temp_rec_cy_it *= -1;	// +
		temp_rec_cx = cx + (r + h * 1 / 4 / 2 + bl_brick_h / 2) * x_ratio;
		temp_rec_cy = cy + (r + h * 1 / 4 / 2 + bl_brick_h / 2) * y_ratio;
		// use 11.5 intead of 12 because of small error
		l_x /= 11.5;
		l_y /= -11.5;
		r_x /= 11.5;
		r_y /= -11.5;
		time = 3;
		while (time--)		// three blocks
		{
			temp_rec_x[0] = temp_rec_cx + bl_brick_h / 2 * x_ratio;
			temp_rec_x[1] = temp_rec_cx - bl_brick_h / 2 * x_ratio;
			temp_rec_y[0] = temp_rec_cy + bl_brick_h / 2 * y_ratio;
			temp_rec_y[1] = temp_rec_cy - bl_brick_h / 2 * y_ratio;
			pDC->MoveTo(temp_rec_x[0] + l_x, temp_rec_y[0] + l_y);
			pDC->LineTo(temp_rec_x[0] + r_x, temp_rec_y[0] + r_y);
			pDC->LineTo(temp_rec_x[1] + r_x, temp_rec_y[1] + r_y);
			pDC->LineTo(temp_rec_x[1] + l_x, temp_rec_y[1] + l_y);
			pDC->LineTo(temp_rec_x[0] + l_x, temp_rec_y[0] + l_y);
			pDC->FloodFill(temp_rec_cx, temp_rec_cy, RGB(255, 255, 255));
			temp_rec_cx += temp_rec_cx_it;
			temp_rec_cy += temp_rec_cy_it;
		}
		//		left-lower
		temp_rec_cx = cx - (r + h * 1 / 4 / 2 + bl_brick_h / 2) * x_ratio - temp_rec_cx_it;
		temp_rec_cy = cy + (r + h * 1 / 4 / 2 + bl_brick_h / 2) * y_ratio + temp_rec_cy_it;
		l_y *= -1;
		r_y *= -1;
		temp_rec_x[0] = temp_rec_cx + bl_brick_h / 2 * x_ratio;
		temp_rec_x[1] = temp_rec_cx - bl_brick_h / 2 * x_ratio;
		temp_rec_y[0] = temp_rec_cy + bl_brick_h / 2 * y_ratio * -1;
		temp_rec_y[1] = temp_rec_cy - bl_brick_h / 2 * y_ratio * -1;
		pDC->MoveTo(temp_rec_x[0] + l_x, temp_rec_y[0] + l_y);
		pDC->LineTo(temp_rec_x[0] + r_x, temp_rec_y[0] + r_y);
		pDC->LineTo(temp_rec_x[1] + r_x, temp_rec_y[1] + r_y);
		pDC->LineTo(temp_rec_x[1] + l_x, temp_rec_y[1] + l_y);
		pDC->LineTo(temp_rec_x[0] + l_x, temp_rec_y[0] + l_y);
		pDC->FloodFill(temp_rec_cx, temp_rec_cy, RGB(255, 255, 255));
		//		right-upper
		temp_rec_cx_it *= 2;	// +
		temp_rec_cy_it *= -2;	// -
		temp_rec_cx = cx + (r + h * 1 / 4 / 2 + bl_brick_h / 2) * x_ratio;
		temp_rec_cy = cy - (r + h * 1 / 4 / 2 + bl_brick_h / 2) * y_ratio;
		time = 2;
		while (time--)		// two blocks
		{
			temp_rec_x[0] = temp_rec_cx + bl_brick_h / 2 * x_ratio;
			temp_rec_x[1] = temp_rec_cx - bl_brick_h / 2 * x_ratio;
			temp_rec_y[0] = temp_rec_cy + bl_brick_h / 2 * y_ratio * -1;
			temp_rec_y[1] = temp_rec_cy - bl_brick_h / 2 * y_ratio * -1;
			pDC->MoveTo(temp_rec_x[0] + l_x, temp_rec_y[0] + l_y);
			pDC->LineTo(temp_rec_x[0] + r_x, temp_rec_y[0] + r_y);
			pDC->LineTo(temp_rec_x[1] + r_x, temp_rec_y[1] + r_y);
			pDC->LineTo(temp_rec_x[1] + l_x, temp_rec_y[1] + l_y);
			pDC->LineTo(temp_rec_x[0] + l_x, temp_rec_y[0] + l_y);
			pDC->FloodFill(temp_rec_cx, temp_rec_cy, RGB(255, 255, 255));
			temp_rec_cx += temp_rec_cx_it;
			temp_rec_cy += temp_rec_cy_it;
		}
		pDC->SelectObject(old_pen);
		pDC->SelectObject(old_brush);
	}
	// TODO: 在此加入原生資料的描繪程式碼
}

/*							Reference:
								national flag:
									ROC:
										https://zh.wikipedia.org/wiki/%E4%B8%AD%E8%8F%AF%E6%B0%91%E5%9C%8B%E5%9C%8B%E6%97%97
										https://en.wikipedia.org/wiki/Flag_of_the_Republic_of_China
									Republic of Azerbaijan:
										https://zh.wikipedia.org/wiki/%E9%98%BF%E5%A1%9E%E6%8B%9C%E7%96%86%E5%9B%BD%E6%97%97
									Korea:
										https://zh.wikipedia.org/wiki/%E5%A4%A7%E9%9F%93%E6%B0%91%E5%9C%8B%E5%9C%8B%E6%97%97#%E8%AE%BE%E8%AE%A1
										https://zh.wikipedia.org/wiki/File:Flag_of_South_Korea.svg
								draw a rectangular:
									https://stackoverflow.com/questions/8560071/rectangle-in-mfc
									https://cboard.cprogramming.com/windows-programming/37788-drawing-mfc.html
									http://forums.codeguru.com/showthread.php?500534-How-Can-fill-Color-in-Rectangle-that-is-Drawn-by-CDC-Rectangle
								draw a circle:
									http://www.functionx.com/visualc/gdi/circles.htm
									http://www.ucancode.net/Visual_C_MFC_COM_Control/CDC_Arc_Pie_Chord.htm
								CPoint:
									https://docs.microsoft.com/zh-tw/cpp/atl-mfc-shared/reference/cpoint-class?view=vs-2019
*/

// CHW10616098黃秉茂View 列印

BOOL CHW10616098黃秉茂View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 預設的準備列印程式碼
	return DoPreparePrinting(pInfo);
}

void CHW10616098黃秉茂View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印前額外的初始設定
}

void CHW10616098黃秉茂View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印後的清除程式碼
}


// CHW10616098黃秉茂View 診斷

#ifdef _DEBUG
void CHW10616098黃秉茂View::AssertValid() const
{
	CView::AssertValid();
}

void CHW10616098黃秉茂View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHW10616098黃秉茂Doc* CHW10616098黃秉茂View::GetDocument() const // 內嵌非偵錯版本
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHW10616098黃秉茂Doc)));
	return (CHW10616098黃秉茂Doc*)m_pDocument;
}
#endif //_DEBUG


// CHW10616098黃秉茂View 訊息處理常式


void CHW10616098黃秉茂View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	num++;
	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}


void CHW10616098黃秉茂View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	num--;
	Invalidate();
	CView::OnRButtonDown(nFlags, point);
}