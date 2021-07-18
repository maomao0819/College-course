/*
Calculate Clean Price and Dirty Price for a bond under actual/actual and 30/360 day count conversion.
Input: Bond maturity and settlement date, bond yield, coupon rate.
Bond is assumed to pay coupons seminnually
*Jasmine Hung 2016.03
*/

#include<iostream>
#include <math.h>
using namespace std;

int n; //remain peroids
int actual; //days to next payment date
int ThreeSixty;  //days to next payment date
double dirty_price, clean_price;

int	actual_day(int y, int m, int d) {   //Rata Die Algorithm
	if (m < 3)
	  {y--, m += 12;}
	return 365 * y + y / 4 - y / 100 + y / 400 + (153 * m - 457) / 5 + d - 306;
}

int calculate_remain_peroid(int M_month, int M_year, int S_month, int S_year, int S_date, int M_date){
	n= actual_day(M_year, M_month, M_date) - actual_day(S_year, S_month, S_date);
	n = (n / 180)+1;
	return n;
}

//Calculate and print dirty_price
double calculate_dirty_price(double r, double w, int n, double par_value, double C){
	w = w / 180.0;
	double a1 = 1 / pow((1 + r), w);
	dirty_price = a1*(pow((1+r), n) - 1) / r;  // geometric progression 等比級數和公式
	dirty_price = C*dirty_price + par_value*pow((1 + r), -w - n + 1);
	cout << "Dirty Price:" << dirty_price << endl;
	return dirty_price;
}

double accrued_interest(int day, double C) {  //day: actual or ThreeSixty
	double interest = C*(1 - (day / 180.0));
	return interest;
}


int ThreeSixty_method(int next_year, int next_month, int S_year,int S_month)
{	if ((next_year - S_year) == 0) {
		return (next_month - S_month) * 30;}
	else  //if cross to the second year
	{return (12 - S_month + next_month) * 30;}
}


void calculate(int M_month, int M_year, int S_month, int S_year, int S_date, double C, double par_value,double yield,int n) {

	// ------- FIND  next_coupon_date ----------
	int first_coupon_month = M_month; // payment month #1
	int second_coupon_month = (M_month + 5) % 12 + 1; //  payment month #2
	int next_month, next_year, min = 999999, ans;
	int temp[5]; // four situations
	temp[1] = actual_day(S_year, first_coupon_month, S_date) - actual_day(S_year, S_month, S_date);
	temp[2] = actual_day(S_year + 1, first_coupon_month, S_date) - actual_day(S_year, S_month, S_date);
	temp[3] = actual_day(S_year, second_coupon_month, S_date) - actual_day(S_year, S_month, S_date);
	temp[4] = actual_day(S_year + 1, second_coupon_month, S_date) - actual_day(S_year, S_month, S_date);

	//Find the min days (from >0)
	for (int i = 1; i <= 4; i++)
	{
		if (temp[i] < 0) temp[i] = temp[i] + 1000; //add a big num to negetive days
	}
	for (int i = 1; i <= 4; i++)
	{
		if (temp[i] < min)
		{
			min = temp[i];
			ans = i;
			actual = min;
		}
	}
	switch (ans)
	{
	case 1: next_year = S_year; next_month = first_coupon_month;
		break;
	case 2: next_year = S_year + 1; next_month = first_coupon_month;
		break;
	case 3: next_year = S_year; next_month = second_coupon_month;
		break;
	case 4: next_year = S_year + 1; next_month = second_coupon_month;
		break;
	}
	cout << endl << "Next coupon payment date:" << next_year << "/" << next_month << "/" << S_date << endl;
	// ------- End of FIND next_coupon_date ----------


	ThreeSixty = ThreeSixty_method(next_year, next_month, S_year, S_month);

	double actual_accrued_interest= accrued_interest(actual, C);
	double ThreeSixty_accrued_interest= accrued_interest(ThreeSixty,C);

	cout << "==== Under actual/actual ===== " << endl;
	cout << "Accrued interest:" << actual_accrued_interest << endl;
	double actual_dirty_price = calculate_dirty_price(yield, actual, n,par_value, C);
	cout << "Clean Price=" << dirty_price- actual_accrued_interest<<endl<<endl;


	cout << "====== Under 30/360 ====== " << endl;
	cout << "Accrued interest:" << ThreeSixty_accrued_interest<<endl;
	double ThreeSixty_dirty_price = calculate_dirty_price(yield, ThreeSixty, n,par_value,C);
	cout << "Clean Price=" << dirty_price - ThreeSixty_accrued_interest << endl;
}


int main()
{
	int M_year, M_month, M_date, S_year, S_month, S_date;
	double yield,coupon, par_value;

	cout << "Input Bond Maturity Date (Year Month Date) : ";
	cin >> M_year >> M_month >> M_date;

	cout << "Input Settlement Date (Year Month Date) : " ;
	cin >> S_year >> S_month >> S_date;

	cout << "Input bond yield:";
	cin >> yield;

	cout << "Input coupon rate:";
	cin >> coupon;

	cout << "Input bond's Face Value:";
	cin >> par_value;

	double C = par_value*coupon/2; //C:每一期的利息

	int n = calculate_remain_peroid(M_month, M_year, S_month, S_year, S_date, M_date);
	calculate(M_month, M_year, S_month, S_year, S_date, C, par_value, yield, n);

    return 0;
}
