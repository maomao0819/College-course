#include "stdafx.h"
#include "CStock.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <atlstr.h>
using namespace std;


CStock::CStock()
{
	no = 0;
	date = NULL;
	open = NULL;
	high = NULL;
	low = NULL;
	close = NULL;
	adj = NULL;
	vol = NULL;
}


CStock::~CStock()
{
	if (date != NULL)
		delete[] date;
	if (open != NULL)
		delete[] open;
	if (high != NULL)
		delete[] high;
	if (low != NULL)
		delete[] low;
	if (close != NULL)
		delete[] close;
	if (adj != NULL)
		delete[] adj;
	if (vol != NULL)
		delete[] vol;
}

void CStock::load(char filepath[], char s[])
{
	char tmp;
	strcpy_s(symbol, s);
	ifstream fin(filepath);
	fin >> no;
	if (date != NULL)
		delete[] date;
	date = new int[no];
	if (open != NULL)
		delete[] open;
	open = new double[no];
	if (high != NULL)
		delete[] high;
	high = new double[no];
	if (low != NULL)
		delete[] low;
	low = new double[no];
	if (close != NULL)
		delete[] close;
	close = new double[no];
	if (adj != NULL)
		delete[] adj;
	adj = new double[no];
	if (vol != NULL)
		delete[] vol;
	vol = new int[no];
	for (int i = 0; i < no; i++)
	{
		fin >> date[i] >> tmp;
		fin >> open[i] >> tmp;
		fin >> high[i] >> tmp;
		fin >> low[i] >> tmp;
		fin >> close[i] >> tmp;
		fin >> adj[i] >> tmp;
		fin >> vol[i];
	}
	fin.close();

}

void CStock::draw(CDC *pDC, int H ,int W ,int n, int pt_x, int* x_line, int* y_line_A, int* y_line_V)
{
	if (no > 0)
	{
		/*CString str;
		str.Format(_T("[%d,%d,%d] Date : %d   Open : %lf   Close : %lf"), H,W, n, date[n], open[n], close[n]);
		pDC->TextOutW(100, 100, str);*/
		int ymin = H / 8;
		int ymax = H * 3 / 4;
		int ymin_vol = H * 4 / 5;
		int ymax_vol = H * 39 / 40;
		double vol_H = (double)(ymax_vol - ymin_vol) * 0.9;
		int N = W / 10;		//畫的筆數
		int i;
		double smax = high[n];
		double smin = low[n];
		double vol_max = vol[n];
		int x1, x2, x3, y1, y2, y3, y4;
		for (i = 1; i < N; i++)		//從最後一筆資料看起
		{
			if (high[n - i] > smax)
				smax = high[n - i];
			if (low[n - i] < smin)
				smin = low[n - i];
			if (vol[n - i] > vol_max)
				vol_max = vol[n - i];
		}
		pDC->MoveTo(0, ymin);
		pDC->LineTo(W, ymin);
		pDC->MoveTo(0, ymax);
		pDC->LineTo(W, ymax);
		pDC->MoveTo(0, ymin_vol);
		pDC->LineTo(W, ymin_vol);
		pDC->MoveTo(0, ymax_vol);
		pDC->LineTo(W, ymax_vol);
		double* MA20 = new double[n - 20 + 1];
		double* MV20 = new double[n - 20 + 1];
		int M20_idx = 0;
		double MA20_pt1 = 0;
		double MA20_pt2 = 0;
		double MV20_pt1 = 0;
		double MV20_pt2 = 0;
		if (N >= 20)
		{
			for (i = 0; i < 20; i++)
			{
				MA20_pt1 += close[n - i];
				MV20_pt1 += vol[n - i];
			}
			MA20[M20_idx] = MA20_pt1;
			MV20[M20_idx++] = MV20_pt1;
		}
		double* MA5 = new double[n - 5 + 1];
		double* MV5 = new double[n - 5 + 1];
		int M5_idx = 0;
		double MA5_pt1 = 0;
		double MA5_pt2 = 0;
		double MV5_pt1 = 0;
		double MV5_pt2 = 0;
		if (N >= 5)
		{
			for (i = 0; i < 5; i++)
			{
				MA5_pt1 += close[n - i];
				MV5_pt1 += vol[n - i];
			}
			MA5[M5_idx] = MA5_pt1;
			MV5[M5_idx++] = MV5_pt1;
		}
		double* MA60 = new double[n - 60 + 1];
		double* MV60 = new double[n - 60 + 1];
		int M60_idx = 0;
		double MA60_pt1 = 0;
		double MA60_pt2 = 0;
		double MV60_pt1 = 0;
		double MV60_pt2 = 0;
		if (N >= 60)
		{
			for (i = 0; i < 60; i++)
			{
				MA60_pt1 += close[n - i];
				MV60_pt1 += vol[n - i];
			}
			MA60[M60_idx] = MA60_pt1;
			MV60[M60_idx++] = MV60_pt1;
		}
		for (i = 0; i < N; i++)
		{
			x3 = W - i * 10 - 1;
			x2 = x3 - 3;
			x1 = x2 - 3;
			//計算高開收低所該出現的Y座標
			y1 = (high[n - i] - smax) / (smin - smax)*(ymax - ymin) + ymin;
			y2 = (open[n - i] - smax) / (smin - smax)*(ymax - ymin) + ymin;
			y3 = (close[n - i] - smax) / (smin - smax)*(ymax - ymin) + ymin;
			y4 = (low[n - i] - smax) / (smin - smax)*(ymax - ymin) + ymin;
			pDC->MoveTo(x1, y2);
			pDC->LineTo(x3, y2);
			pDC->LineTo(x3, y3);
			pDC->LineTo(x1, y3);
			pDC->LineTo(x1, y2);
			CBrush *old_brush;
			if (y2 > y3 && i < n)
			{
				CBrush green_brush;
				green_brush.CreateSolidBrush(RGB(0, 128, 0));
				old_brush = pDC->SelectObject(&green_brush);
				pDC->FloodFill(x2, (y2 + y3) / 2, RGB(0, 0, 0));	
				//								  所受局限之RGB
			}
			else if (y2 < y3 && i < n)
			{
				CBrush red_brush;
				red_brush.CreateSolidBrush(RGB(255, 0, 0));
				old_brush = pDC->SelectObject(&red_brush);
				pDC->FloodFill(x2, (y2 + y3) / 2, RGB(0, 0, 0));
			}
			pDC->MoveTo(x2, y1);
			pDC->LineTo(x2, y4);
			double y_vol = ymax_vol - (double)vol[n - i] / vol_max * vol_H ;
			pDC->MoveTo(x2, ymax_vol);
			pDC->LineTo(x2, y_vol);
			pDC->LineTo(x3 + 1, y_vol);
			pDC->LineTo(x3 + 1, ymax_vol);
			if (i == n)
			{
				CBrush dimgray_brush;
				dimgray_brush.CreateSolidBrush(RGB(105, 105, 105));
				old_brush = pDC->SelectObject(&dimgray_brush);
				pDC->FloodFill((x2 + x3) / 2, (ymax_vol + y_vol) / 2, RGB(0, 0, 0));
			}
			else if (low[n - i] < low[n - i - 1] && i < n)
			{
				CBrush green_brush;
				green_brush.CreateSolidBrush(RGB(0, 128, 0));
				old_brush = pDC->SelectObject(&green_brush);
				pDC->FloodFill((x2 + x3) / 2, (ymax_vol + y_vol) / 2, RGB(0, 0, 0));
			}
			else if (low[n - i] > low[n - i - 1] && i < n)
			{
				CBrush red_brush;
				red_brush.CreateSolidBrush(RGB(255, 0, 0));
				old_brush = pDC->SelectObject(&red_brush);
				pDC->FloodFill((x2 + x3) / 2, (ymax_vol + y_vol) / 2, RGB(0, 0, 0));
			}
			else if (low[n - i] == low[n - i - 1] && i < n)
			{
				CBrush dimgray_brush;
				dimgray_brush.CreateSolidBrush(RGB(105, 105, 105));
				old_brush = pDC->SelectObject(&dimgray_brush);
				pDC->FloodFill((x2 + x3) / 2, (ymax_vol + y_vol) / 2, RGB(0, 0, 0));
			}
			if (date[n - i] - date[n - i - 1] > 50 && i < n)		//每個月初畫平行Y軸的輔助線
			{
				int y_drawline = ymin;
				while (y_drawline < ymax)
				{
					if (y_drawline < y1 && y_drawline > y4)
						y_drawline += 5;
					else
					{
						pDC->MoveTo(x2, y_drawline += 5);
						pDC->LineTo(x2, y_drawline += 5);
					}
				}
				y_drawline = ymin_vol;
				while (y_drawline < y_vol)
				{
						pDC->MoveTo(x2, y_drawline += 5);
						pDC->LineTo(x2, y_drawline += 5);
				}
			}
			if (MA20_pt1 != 0 && N - i >= 20 && i > 0 && i < n)
			{
				MA20_pt2 = MA20_pt1 - close[n - i + 1] + close[n - i - 20 + 1];
				MA20[M20_idx] = MA20_pt2;
				MV20_pt2 = MV20_pt1 - vol[n - i + 1] + vol[n - i - 20 + 1];
				MV20[M20_idx++] = MV20_pt2;
				CPen darkorange_pen, *old_pen;
				darkorange_pen.CreatePen(PS_SOLID, 1, RGB(255, 140, 0));
				old_pen = pDC->SelectObject(&darkorange_pen);
				pDC->MoveTo(x2 + 10, (MA20_pt1 / 20 - smax) / (smin - smax)*(ymax - ymin) + ymin);
				pDC->LineTo(x2, (MA20_pt2 / 20 - smax) / (smin - smax)*(ymax - ymin) + ymin);
				pDC->MoveTo((x2 + x3 + 1) / 2 + 10, ymax_vol - MV20_pt1 / 20 / vol_max * vol_H);
				pDC->LineTo((x2 + x3 + 1) / 2, ymax_vol - MV20_pt2 / 20 / vol_max * vol_H);
				pDC->SelectObject(old_pen);
				MA20_pt1 = MA20_pt2;
				MV20_pt1 = MV20_pt2;
			}
			if (MA5_pt1 != 0 && N - i >= 5 && i > 0 && i < n)
			{
				MA5_pt2 = MA5_pt1 - close[n - i + 1] + close[n - i - 5 + 1];
				MA5[M5_idx] = MA5_pt2;
				MV5_pt2 = MV5_pt1 - vol[n - i + 1] + vol[n - i - 5 + 1];
				MV5[M5_idx++] = MV5_pt2;
				CPen mediumblue_pen, *old_pen;
				mediumblue_pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 205));
				old_pen = pDC->SelectObject(&mediumblue_pen);
				pDC->MoveTo(x2 + 10, (MA5_pt1 / 5 - smax) / (smin - smax)*(ymax - ymin) + ymin);
				pDC->LineTo(x2, (MA5_pt2 / 5 - smax) / (smin - smax)*(ymax - ymin) + ymin);
				pDC->MoveTo((x2 + x3 + 1) / 2 + 10, ymax_vol - MV5_pt1 / 5 / vol_max * vol_H);
				pDC->LineTo((x2 + x3 + 1) / 2, ymax_vol - MV5_pt2 / 5 / vol_max * vol_H);
				pDC->SelectObject(old_pen);
				MA5_pt1 = MA5_pt2;
				MV5_pt1 = MV5_pt2;
			}
			if (MA60_pt1 != 0 && N - i >= 60 && i > 0 && i < n)
			{
				MA60_pt2 = MA60_pt1 - close[n - i + 1] + close[n - i - 60 + 1];
				MA60[M60_idx] = MA60_pt2;
				MV60_pt2 = MV60_pt1 - vol[n - i + 1] + vol[n - i - 60 + 1];
				MV60[M60_idx++] = MV60_pt2;
				CPen forestgreen_pen, *old_pen;
				forestgreen_pen.CreatePen(PS_SOLID, 1, RGB(34, 139, 34));
				old_pen = pDC->SelectObject(&forestgreen_pen);
				pDC->MoveTo(x2 + 10, (MA60_pt1 / 60 - smax) / (smin - smax)*(ymax - ymin) + ymin);
				pDC->LineTo(x2, (MA60_pt2 / 60 - smax) / (smin - smax)*(ymax - ymin) + ymin);
				pDC->MoveTo((x2 + x3 + 1) / 2 + 10, ymax_vol - MV60_pt1 / 60 / vol_max * vol_H);
				pDC->LineTo((x2 + x3 + 1) / 2, ymax_vol - MV60_pt2 / 60 / vol_max * vol_H);
				pDC->SelectObject(old_pen);
				MA60_pt1 = MA60_pt2;
				MV60_pt1 = MV60_pt2;
			}
			int dis_cur = W - pt_x;		
			if (dis_cur % 10 < 7)
				if(dis_cur / 10 == i)
					*x_line = x2;
		}
		for (int i = 1; i <= 3; i++)	//畫平行X軸的輔助線
		{
			int x_drawline_y = (ymax - ymin) * i / 4 + ymin;
			int x_drawline = W - 8;
			while (x_drawline > 0)
			{
				pDC->MoveTo(x_drawline, x_drawline_y);
				pDC->LineTo(x_drawline - 2, x_drawline_y);
				x_drawline -= 10;
			}
			x_drawline_y = (ymax_vol - ymin_vol) * i / 4 + ymin_vol;
			x_drawline = W - 8;
			while (x_drawline > 0)
			{
				pDC->MoveTo(x_drawline, x_drawline_y);
				pDC->LineTo(x_drawline - 2, x_drawline_y);
				x_drawline -= 10;
			}
		}
		POINT pt;
		/*while (1)
		{
			BOOL bReturn = GetCursorPos(&pt);	//獲取滑鼠指標位置到pt
			if (bReturn != 0)					//如果函式執行成功
				break;
		}*/
		int dis_cur = W - pt_x;		//輸出文字
		if (dis_cur % 10 < 7)
		{
			int num_cur = dis_cur / 10;
			CString str;
			str = "Date : ";
			string temp_int = to_string(date[n - num_cur]);
			temp_int.insert(4, 1, '/');
			temp_int.insert(7, 1, '/');
			CString temp_date(temp_int.c_str());
			str += temp_date;
			str += "  Open : ";
			string temp_double = to_string(open[n - num_cur]);
			CString temp_open(temp_double.c_str());
			str += temp_open;
			str += ", High : ";
			temp_double = to_string(high[n - num_cur]);
			CString temp_high(temp_double.c_str());
			str += temp_high;
			str += ", Low : ";
			temp_double = to_string(low[n - num_cur]);
			CString temp_low(temp_double.c_str());
			str += temp_low;
			str += ", Close : ";
			*y_line_A = (close[n - num_cur] - smax) / (smin - smax)*(ymax - ymin) + ymin;
			temp_double = to_string(close[n - num_cur]);
			CString temp_close(temp_double.c_str());
			str += temp_close;
			str += ", Vol : ";
			*y_line_V = ymax_vol - vol[n - num_cur] / vol_max * vol_H;
			temp_double = to_string(vol[n - num_cur]);
			CString temp_vol(temp_double.c_str());
			str += temp_vol;
			if (num_cur < n)
			{
				str += ", Chg : ";
				double diff = low[n - num_cur] - low[n - num_cur - 1];
				if (diff >= 0)
					str += "+";
				temp_double = to_string(diff);
				CString temp_vol(temp_double.c_str());
				str += temp_vol;
			}
			pDC->TextOut(W * 3 / 32, ymin / 4, str);
			CString str2;
			str2 = " MA5 : ";
			if (num_cur <= N - 5)
			{
				temp_double = to_string(MA5[num_cur] / 5);
				CString temp_MA5(temp_double.c_str());
				str2 += temp_MA5;
				if (num_cur <= N - 5 - 1)
				{
					if (MA5[num_cur] > MA5[num_cur + 1])
						str2 += " I ";
					else if (MA5[num_cur] < MA5[num_cur + 1])
						str2 += " D ";
				}
				
			}
			else
				str2 += "- ";
			str2 += ", MA20 : ";
			if (num_cur <= N - 20)
			{
				temp_double = to_string(MA20[num_cur] / 20);
				CString temp_MA20(temp_double.c_str());
				str2 += temp_MA20;
				if (num_cur <= N - 20 - 1)
				{
					if (MA20[num_cur] > MA20[num_cur + 1])
						str2 += " I ";
					else if (MA20[num_cur] < MA20[num_cur + 1])
						str2 += " D ";
				}
			}
			else
				str2 += "- ";
			str2 += ", MA60 : ";
			if (num_cur <= N - 60)
			{
				temp_double = to_string(MA60[num_cur] / 60);
				CString temp_MA60(temp_double.c_str());
				str2 += temp_MA60;
				if (num_cur <= N - 60 - 1)
				{
					if (MA60[num_cur] > MA60[num_cur + 1])
						str2 += " I ";
					else if (MA60[num_cur] < MA60[num_cur + 1])
						str2 += " D ";
				}
			}
			else
				str2 += "- ";
			pDC->TextOut(W * 3 / 32, ymin / 4 * 3, str2);
			CString str3;
			str3 = " Vol : ";
			str3 += temp_vol;
			str3 += ", MV5 : ";
			if (num_cur <= N - 5)
			{
				temp_double = to_string(MV5[num_cur] / 5);
				CString temp_MV5(temp_double.c_str());
				str3 += temp_MV5;
				if (num_cur <= N - 5 - 1)
				{
					if (MV5[num_cur] > MV5[num_cur + 1])
						str3 += " I ";
					else if (MV5[num_cur] < MV5[num_cur + 1])
						str3 += " D ";
				}
			}
			else
				str3 += "- ";
			str3 += ", MV20 : ";
			if (num_cur <= N - 20)
			{
				temp_double = to_string(MV20[num_cur] / 20);
				CString temp_MV20(temp_double.c_str());
				str3 += temp_MV20;
				if (num_cur <= N - 20 - 1)
				{
					if (MV20[num_cur] > MV20[num_cur + 1])
						str3 += " I ";
					else if (MV20[num_cur] < MV20[num_cur + 1])
						str3 += " D ";
				}
			}
			else
				str3 += "- ";
			str3 += ", MV60 : ";
			if (num_cur <= N - 60)
			{
				temp_double = to_string(MV60[num_cur] / 60);
				CString temp_MV60(temp_double.c_str());
				str3 += temp_MV60;
				if (num_cur <= N - 60 - 1)
				{
					if (MV60[num_cur] > MV60[num_cur + 1])
						str3 += " I ";
					else if (MV60[num_cur] < MV60[num_cur + 1])
						str3 += " D ";
				}
			}
			else
				str3 += "- ";
			pDC->TextOut(W * 3 / 32, (ymax * 3 + ymin_vol) / 4, str3);
		}
	}
}


//		Reference:
//			GetCursorPos	獲取滑鼠指標位置 (不是我需要的)
//				https://www.itread01.com/content/1544653293.html
//			pDC->TextOut	輸出文字
//				https://blog.csdn.net/hongxingabc/article/details/48594311
//							CString
//				https://www.itsfun.com.tw/CString/wiki-7380625-9234305
//							int 2 CString (有bug)
//				http://www.programmer-club.com.tw/ShowSameTitleN/vc/22331.html
//				https://blog.csdn.net/h_kingone/article/details/72973224
//			to_string		double 2 string
//				https://stackoverflow.com/questions/332111/how-do-i-convert-a-double-into-a-string-in-c
//							string 2 CString
//				https://stackoverflow.com/questions/19616828/how-to-convert-stdstring-to-cstring-in-unicode-project
//			insert			insert char to string
//				https://stackoverflow.com/questions/3223302/c-insert-char-to-a-string
//			(CString) +=
//				https://docs.microsoft.com/zh-tw/cpp/atl-mfc-shared/basic-cstring-operations?view=vs-2019
