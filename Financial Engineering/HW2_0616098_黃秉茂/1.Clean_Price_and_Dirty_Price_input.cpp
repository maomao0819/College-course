#include <iostream>
#include <math.h>
#include <cstdlib> // atoi 函數所在函式庫
#include <string>
using namespace std;

void Split_Date(string date, int& year, int& month, int& day);
int Rata_Die(int year, int month, int day); // Rata Die day
int Duration_actual_actual(int M_year, int M_month, int M_day, int S_year, int S_month, int S_day);
int Duration_30_360(int M_year, int M_month, int M_day, int S_year, int S_month, int S_day);
int Remain_Day_actual_actual(int M_year, int M_month, int M_day, int S_year, int S_month, int S_day);
int Remain_Day_30_360(int duration, int n_coupon_period);
int Coupon_Period_actual_actual(int n, int M_month, int S_year);
double Calculate_w(int n_remain_day, int n_coupon_period);
double Dirty_Price(double par_value, double coupon, double bond_yield, double w, int n_remain_peroid);
double Accrued_Interest(double coupon, double w);
double Clean_Price(double dirty_price, double accrued_interest);

int main()
{
    // declaration and initialization
    string maturity_date, settlement_date;
    double bond_yield = 0, coupon_rate = 0;
    int interest_frequency = 2;
    int n_coupon_period_30_360 = 360 / interest_frequency, n_coupon_period_actual_actual = 365 / interest_frequency;
    int year_maturity = 0, month_maturity = 0, day_maturity = 0;
    int year_settlement = 0, month_settlement = 0, day_settlement = 0;
    double par_value = 100, coupon = 0;
    int n_remain_peroid = 0;

    // input
    cout << "Please input the bond maturity date (YYYY/MM/DD): ";
    cin >> maturity_date;
    cout << "Please input the settlement date (YYYY/MM/DD): ";
    cin >> settlement_date;
    Split_Date(maturity_date, year_maturity, month_maturity, day_maturity);
    Split_Date(settlement_date, year_settlement, month_settlement, day_settlement);
    // int duration_actual_actual = Duration_actual_actual(year_maturity, month_maturity, day_maturity, year_settlement, month_settlement, day_settlement);
    int duration_30_360 = Duration_30_360(year_maturity, month_maturity, day_maturity, year_settlement, month_settlement, day_settlement);
    // wrong input
    while (duration_30_360 < 1)
    {
        cout << "ERROR! The bond maturity date must BIGGER THAN the settlement date! Please input again!\n";
        cout << "Please input the bond maturity date (YYYY/MM/DD): ";
        cin >> maturity_date;
        cout << "Please input the settlement date (YYYY/MM/DD): ";
        cin >> settlement_date;
        Split_Date(maturity_date, year_maturity, month_maturity, day_maturity);
        Split_Date(settlement_date, year_settlement, month_settlement, day_settlement);
        // duration_actual_actual = Duration_actual_actual(year_maturity, month_maturity, day_maturity, year_settlement, month_settlement, day_settlement);
        duration_30_360 = Duration_30_360(year_maturity, month_maturity, day_maturity, year_settlement, month_settlement, day_settlement);
    }
    cout << "Please input the bond yield: ";
    cin >> bond_yield;
    bond_yield /= interest_frequency;
    cout << "Please input the coupon rate: ";
    cin >> coupon_rate;

    coupon = par_value * coupon_rate / interest_frequency;
    n_remain_peroid = duration_30_360 / n_coupon_period_30_360;

    cout << "==== Under actual/actual =====\n";
    int n_remain_day_actual_actual = Remain_Day_actual_actual(year_maturity, month_maturity, day_maturity, year_settlement, month_settlement, day_settlement);
    n_coupon_period_actual_actual = Coupon_Period_actual_actual(n_remain_peroid, month_maturity, year_settlement);
    double w_actual_actual = Calculate_w(n_remain_day_actual_actual, n_coupon_period_actual_actual);
    double dirty_price_actual_actual = Dirty_Price(par_value, coupon, bond_yield, w_actual_actual, n_remain_peroid);
    double accrued_interest_actual_actual = Accrued_Interest(coupon, w_actual_actual);
    double clean_price_actual_actual = Clean_Price(dirty_price_actual_actual, accrued_interest_actual_actual);
    cout << "dirty price: " << dirty_price_actual_actual << endl;
    cout << "clean price: " << clean_price_actual_actual << endl;
    cout << "====== Under 30/360 ======\n";
    int n_remain_day_30_360 = Remain_Day_30_360(duration_30_360, n_coupon_period_30_360);
    double w_30_360 = Calculate_w(n_remain_day_30_360, n_coupon_period_30_360);
    double dirty_price_30_360 = Dirty_Price(par_value, coupon, bond_yield, w_30_360, n_remain_peroid);
    double accrued_interest_30_360 = Accrued_Interest(coupon, w_30_360);
    double clean_price_30_360 = Clean_Price(dirty_price_30_360, accrued_interest_30_360);
    cout << "dirty price: " << dirty_price_30_360 << endl;
    cout << "clean price: " << clean_price_30_360;
    return 0;
}

void Split_Date(string date, int& year, int& month, int& day)
{
    string delimiter = "/";
    int year_location = date.find(delimiter);
    string str_year = date.substr(0, year_location);
    year = atoi(str_year.c_str());
    string str_month = date.substr(year_location + 1, 2);
    month = atoi(str_month.c_str());
    int month_location = date.find(delimiter, year_location + 1);
    string str_day = date.substr(month_location + 1, 2);
    day = atoi(str_day.c_str());
    return;
}

int Rata_Die(int year, int month, int day)  // Rata Die day
{
    if (month < 3)
        year--, month += 12;
    // 365: 1 year  /4, /100, /400: leap year   153: 5 month Mar ~ Jul, Aug ~ Dec   306: Mar ~ Dec
    return 365 * year + year / 4 - year / 100 + year / 400 + (153 * month - 457) / 5 + day - 306;
}

int Duration_actual_actual(int M_year, int M_month, int M_day, int S_year, int S_month, int S_day)
{
    return Rata_Die(M_year, M_month, M_day) - Rata_Die(S_year, S_month, S_day);
}

int Duration_30_360(int M_year, int M_month, int M_day, int S_year, int S_month, int S_day)
{
    if (M_day < S_day)
    {
        M_day += 30;
        M_month--;
    }
    if (M_month < S_month)
    {
        M_month += 12;
        M_year--;
    }
    return (((M_year - S_year) * 12) + (M_month - S_month)) * 30 + (M_day - S_day);
}

int Remain_Day_actual_actual(int M_year, int M_month, int M_day, int S_year, int S_month, int S_day)
{
    if (M_month > S_month)
    {
        if ((M_month - S_month) > 6)
            M_month -=6;
        return Duration_actual_actual(S_year, M_month, M_day, S_year, S_month, S_day);
    }
    else
    {
        M_month += 6;
        int plus_year = 0;
        if (M_month > 12)
            return Duration_actual_actual(S_year + 1, M_month - 12, M_day, S_year, S_month, S_day);
        return Duration_actual_actual(S_year, M_month, M_day, S_year, S_month, S_day);
    }
}

int Remain_Day_30_360(int duration, int n_coupon_period)
{
    return duration % n_coupon_period;
}

int Coupon_Period_actual_actual(int n, int M_month, int S_year)
{
    if (n % 2)
    {
        M_month = (M_month + 6) % 12;
        if (M_month == 0)
            M_month = 12;
    }
    if (M_month > 6)
        return Duration_actual_actual(S_year, M_month, 1, S_year, M_month - 6, 1);
    else
        return Duration_actual_actual(S_year + 1, M_month, 1, S_year, M_month + 6, 1);
}

double Calculate_w(int n_remain_day, int n_coupon_period)
{
    return ((double)n_remain_day / (double)n_coupon_period);
}

double Dirty_Price(double par_value, double coupon, double bond_yield, double w, int n_remain_peroid)
{
    double discount = 1 + bond_yield;
    double coupon_rate_each = coupon / pow(discount, w);
    double price = coupon_rate_each;
    for (int i = 0; i < n_remain_peroid; i++)
    {
        coupon_rate_each /= discount;
        price += coupon_rate_each;
    }
    price += coupon_rate_each / coupon * par_value;
    return price;
}

double Accrued_Interest(double coupon, double w)
{
    return coupon * (1 - w);
}

double Clean_Price(double dirty_price, double accrued_interest)
{
    return dirty_price - accrued_interest;
}
