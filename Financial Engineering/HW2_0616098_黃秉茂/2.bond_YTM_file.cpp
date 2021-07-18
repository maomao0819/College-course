#include <iostream>
#include <math.h>
#include <cstdlib> // atoi 函數所在函式庫
#include <string>
#include <fstream>
#include <vector>
#include <utility> // pair
#include <stdexcept> // runtime_error
#include <sstream> // stringstream
using namespace std;

#define par_value 100
#define tolerance 0.0001

vector<pair<string, vector<string> > > read_csv(string filename);
vector<string> split_string(const string& str, const char& delimiter);
int Rata_Die(int year, int month, int day); // Rata Die day
int Duration_actual_actual(int M_year, int M_month, int M_day, int S_year, int S_month, int S_day);
int Duration_30_360(int M_year, int M_month, int M_day, int S_year, int S_month, int S_day);
int Remain_Day_actual_actual(int M_year, int M_month, int M_day, int S_year, int S_month, int S_day);
int Remain_Day_30_360(int duration, int n_coupon_period);
int Coupon_Period_actual_actual(int n, int M_month, int S_year);
double Calculate_w(int n_remain_day, int n_coupon_period);
double Dirty_Price(double par_val, double coupon, double bond_yield, double w, int n_remain_peroid);
double Accrued_Interest(double coupon, double w);
double Clean_Price(double dirty_price, double accrued_interest);
double Bond_Price_Rate_actual_actual(int M_year, int M_month, int M_day, int S_year, int S_month, int S_day, int interest_frequency, double coupon, double bond_yield);
double Bond_Price_Rate_30_360(int M_year, int M_month, int M_day, int S_year, int S_month, int S_day, int interest_frequency, double coupon, double bond_yield);

int main()
{
    // declaration and initialization
    vector<pair<string, vector<string> > > file = read_csv("issuer_data.csv");
    int n_data = file.at(1).second.size();
    for (int data_idx = 0; data_idx < n_data; data_idx++)
    {
        string maturity_date = file.at(1).second.at(data_idx);
        std::vector<std::string> maturity_date_split = split_string(maturity_date, '/');
        int year_maturity = atoi(maturity_date_split[0].c_str());
        int month_maturity = atoi(maturity_date_split[1].c_str());
        int day_maturity = atoi(maturity_date_split[2].c_str());
        string settlement_date = file.at(2).second.at(data_idx);
        std::vector<std::string> settlement_date_split = split_string(settlement_date, '/');
        int year_settlement = atoi(settlement_date_split[0].c_str());
        int month_settlement = atoi(settlement_date_split[1].c_str());
        int day_settlement = atoi(settlement_date_split[2].c_str());
        double bond_price_rate = atof(file.at(3).second.at(data_idx).c_str()) / 100;
        double bond_price = par_value * bond_price_rate;
        double bond_yield_real = atof(file.at(4).second.at(data_idx).c_str());
        int interest_frequency = atoi(file.at(5).second.at(data_idx).c_str());
        double coupon_rate = atof(file.at(6).second.at(data_idx).c_str()) / 100;
        double coupon = par_value * coupon_rate / interest_frequency;

        cout << "OFFERING_YIELD is " << bond_yield_real << ".\n";

        double bond_yield_actual_actual_high = 1;
        double bond_yield_actual_actual_low = 0;
        cout << "==== Under actual/actual =====\n";
        while (bond_yield_actual_actual_high - bond_yield_actual_actual_low > tolerance)
        {
            double bond_yield_actual_actual_middle = (bond_yield_actual_actual_low + bond_yield_actual_actual_high) / 2;
            double bond_price_rate_actual_actual_guess = Bond_Price_Rate_actual_actual(year_maturity, month_maturity, day_maturity, year_settlement, month_settlement, day_settlement, interest_frequency, coupon, bond_yield_actual_actual_middle);
            if (bond_price_rate_actual_actual_guess * par_value > bond_price)
                bond_yield_actual_actual_low = bond_yield_actual_actual_middle;
            else
                bond_yield_actual_actual_high = bond_yield_actual_actual_middle;
        }
        bond_yield_actual_actual_high *= 100;
        cout << "The computed bond YTM is " << bond_yield_actual_actual_high << ".\n";
        cout << "The error of YTM is " << bond_yield_real - bond_yield_actual_actual_high << ".\n";

        double bond_yield_30_360_high = 1;
        double bond_yield_30_360_low = 0;
        cout << "==== Under 30/360 =====\n";
        while (bond_yield_30_360_high - bond_yield_30_360_low > tolerance)
        {
            double bond_yield_30_360_middle = (bond_yield_30_360_low + bond_yield_30_360_high) / 2;
            double bond_price_rate_30_360_guess = Bond_Price_Rate_30_360(year_maturity, month_maturity, day_maturity, year_settlement, month_settlement, day_settlement, interest_frequency, coupon, bond_yield_30_360_middle);
            if (bond_price_rate_30_360_guess * par_value > bond_price)
                bond_yield_30_360_low = bond_yield_30_360_middle;
            else
                bond_yield_30_360_high = bond_yield_30_360_middle;
        }
        bond_yield_30_360_high *= 100;
        cout << "The computed bond YTM is " << bond_yield_30_360_high << ".\n";
        cout << "The error of YTM is " << bond_yield_real - bond_yield_30_360_high << ".\n";

        cout << endl;
    }
    return 0;
}

vector<pair<string, vector<string> > > read_csv(string filename)
{
    // Reads a CSV file into a vector of <string, vector<string>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, string vector> pairs to store the result
    vector<pair<string, vector<string> > > result;
    // Create an input filestream
    ifstream myFile(filename.c_str());
    // Make sure the file is open
    if (!myFile.is_open())
        throw runtime_error("Could not open file");

    // Helper vars
    string line, colname;
    string val;
    // Read the column names
    if (myFile.good())
    {
        // Extract the first line in the file
        getline(myFile, line);
        // Create a stringstream from line
        stringstream ss(line);
        // Extract each column name
        while (getline(ss, colname, ','))
            // Initialize and add <colname, int vector> pairs to result
            result.push_back({colname, vector<string> {}});
    }
    // Read data, line by line
    while (getline(myFile, line))
    {
        // Create a stringstream of the current line
        stringstream ss(line);
        // Keep track of the current column index
        int colIdx = 0;
        // Extract each value
        while (getline(ss, val, ','))
        {
            result.at(colIdx).second.push_back(val);
            colIdx++;
        }
    }
    // Close file
    myFile.close();
    return result;
}

vector<string> split_string(const string& str, const char& delimiter)
{
    string next;
    vector<string> result;

    // For each character in the string
    for (string::const_iterator it = str.begin(); it != str.end(); it++)
    {
        // If we've hit the terminal character
        if (*it == delimiter)
        {
            // If we have some characters accumulated
            if (!next.empty())
            {
                // Add them to the result vector
                result.push_back(next);
                next.clear();
            }
        }
        else
            // Accumulate the next character into the sequence
            next += *it;
    }
    if (!next.empty())
         result.push_back(next);
    return result;
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

double Dirty_Price(double par_val, double coupon, double bond_yield, double w, int n_remain_peroid)
{
    double discount = 1 + bond_yield;
    double coupon_rate_each = coupon / pow(discount, w);
    double price = coupon_rate_each;
    for (int i = 0; i < n_remain_peroid; i++)
    {
        coupon_rate_each /= discount;
        price += coupon_rate_each;
    }
    price += coupon_rate_each / coupon * par_val;
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

double Bond_Price_Rate_actual_actual(int M_year, int M_month, int M_day, int S_year, int S_month, int S_day, int interest_frequency, double coupon, double bond_yield)
{
    bond_yield /= interest_frequency;
    int n_coupon_period_30_360 = 360 / interest_frequency;
    int duration_30_360 = Duration_30_360(M_year, M_month, M_day, S_year, S_month, S_day);
    int n_remain_peroid = duration_30_360 / n_coupon_period_30_360;
    int n_remain_day_actual_actual = Remain_Day_actual_actual(M_year, M_month, M_day, S_year, S_month, S_day);
    int n_coupon_period_actual_actual = Coupon_Period_actual_actual(n_remain_peroid, M_month, S_year);
    double w_actual_actual = Calculate_w(n_remain_day_actual_actual, n_coupon_period_actual_actual);
    double dirty_price_actual_actual = Dirty_Price(par_value, coupon, bond_yield, w_actual_actual, n_remain_peroid);
    double accrued_interest_actual_actual = Accrued_Interest(coupon, w_actual_actual);
    double clean_price_actual_actual = Clean_Price(dirty_price_actual_actual, accrued_interest_actual_actual);
    return clean_price_actual_actual / 100;
}

double Bond_Price_Rate_30_360(int M_year, int M_month, int M_day, int S_year, int S_month, int S_day, int interest_frequency, double coupon, double bond_yield)
{
    bond_yield /= interest_frequency;
    int n_coupon_period_30_360 = 360 / interest_frequency;
    int duration_30_360 = Duration_30_360(M_year, M_month, M_day, S_year, S_month, S_day);
    int n_remain_day_30_360 = Remain_Day_30_360(duration_30_360, n_coupon_period_30_360);
    double w_30_360 = Calculate_w(n_remain_day_30_360, n_coupon_period_30_360);
    int n_remain_peroid = duration_30_360 / n_coupon_period_30_360;
    double dirty_price_30_360 = Dirty_Price(par_value, coupon, bond_yield, w_30_360, n_remain_peroid);
    double accrued_interest_30_360 = Accrued_Interest(coupon, w_30_360);
    double clean_price_30_360 = Clean_Price(dirty_price_30_360, accrued_interest_30_360);
    return clean_price_30_360 / 100;
}
