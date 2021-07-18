#include "stdafx.h"
#include "CStock.h"
#include <fstream>
#include <iostream>
using namespace std;

CStock::CStock(char s[])
{
	date = NULL;
	open = NULL;
	high = NULL;
	low = NULL;
	close = NULL;
	adj = NULL;
	vol = NULL;
	strcpy(symbol, s);
	load();
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

void CStock::load()
{
	char filename[100];
	strcpy(filename, symbol);
	strcat(filename, ".csv");
	ifstream fin(filename);
	fin >> no;
	if (date != NULL)
		delete[] date;
	date = new int(no);
	if (open != NULL)
		delete[] open;
	open = new double(no);
	if (high != NULL)
		delete[] high;
	high = new double(no);
	if (low != NULL)
		delete[] low;
	low = new double(no);
	if (close != NULL)
		delete[] close;
	close = new double(no);
	if (adj != NULL)
		delete[] adj;
	adj = new double(no);
	if (vol != NULL)
		delete[] vol;
	vol = new int(no);
	for (int i = 0; i < no; i++)
	{
		fin >> date[i];
		fin >> open[i];
		fin >> high[i];
		fin >> low[i];
		fin >> close[i];
		fin >> adj[i];
		fin >> vol[i];
	}
	fin.close();
}