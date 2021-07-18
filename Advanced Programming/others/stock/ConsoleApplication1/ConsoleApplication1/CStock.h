#pragma once
class CStock
{
public:
	CStock(char[]);
	~CStock();
	int no;
	char symbol[20];
	void load();
	double readclose(int day) { return close[day]; }
private:
	int *date;
	double *open;
	double *high;
	double *low;
	double *close;
	double *adj;
	int *vol;
};

