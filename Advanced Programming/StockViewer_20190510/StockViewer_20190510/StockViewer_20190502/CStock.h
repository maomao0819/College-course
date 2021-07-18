#pragma once
class CStock
{
public:
	CStock();
	~CStock();
	int no;
	char symbol[20];
	void load(char[], char[]);
	void draw(CDC* pDC, int H, int W, int n, int pt_x, int* x_line, int* y_line_A, int* y_line_V);
private:
	int *date;
	double *open;
	double *high;
	double *low;
	double *close;
	double *adj;
	int *vol;

};

