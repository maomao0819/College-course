#include <iostream>
#include <math.h>
#include <cstdlib> // atoi
#include <string>
#include <fstream>
#include <vector>
#include <utility> // pair
#include <stdexcept> // runtime_error
#include <sstream> // stringstream
using namespace std;
#define FACE_VALUE 100

vector<pair<string, vector<string> > > read_csv(string filename);
vector<string> split_string(const string& str, const char& delimiter);
int calculate_n_terms(int M_year, int M_month, int S_year, int S_month, int interest_frequency);
float calculate_Macaulay_Duration(int n_terms, float bond_price, float coupon, float yield, int interest_frequency);
float calculate_Modified_Duration(float Macaulay_Duration, float yield);

int main()
{
    // declaration and initialization
    vector<pair<string, vector<string> > > file = read_csv("issuer_data.csv");
    int n_data = file.at(1).second.size();
    cout << "n_data " << n_data << endl;
    for (int data_idx = 0; data_idx < n_data; data_idx++)
    {
        // declaration and initialization
        string maturity_date = file.at(1).second.at(data_idx);
        std::vector<std::string> maturity_date_split = split_string(maturity_date, '/');
        int year_maturity = atoi(maturity_date_split[0].c_str());
        int month_maturity = atoi(maturity_date_split[1].c_str());
        string settlement_date = file.at(2).second.at(data_idx);
        std::vector<std::string> settlement_date_split = split_string(settlement_date, '/');
        int year_settlement = atoi(settlement_date_split[0].c_str());
        int month_settlement = atoi(settlement_date_split[1].c_str());
        double bond_price_rate = atof(file.at(3).second.at(data_idx).c_str()) / 100;
        double bond_price = FACE_VALUE * bond_price_rate;
        double bond_yield = atof(file.at(4).second.at(data_idx).c_str()) / 100;
        int interest_frequency = atoi(file.at(5).second.at(data_idx).c_str());
        bond_yield /= interest_frequency;
        double coupon_rate = atof(file.at(6).second.at(data_idx).c_str()) / 100;
        double coupon = FACE_VALUE * coupon_rate / interest_frequency;
        int n_terms = calculate_n_terms(year_maturity, month_maturity, year_settlement, month_settlement, interest_frequency);
        float Macaulay_Duration = calculate_Macaulay_Duration(n_terms, bond_price, coupon, bond_yield, interest_frequency);
        float Modified_Duration = calculate_Modified_Duration(Macaulay_Duration, bond_yield);
        // output
        cout << "index: " << data_idx << endl;
        cout << "Macaulay Duration:" << Macaulay_Duration << " years." << endl;
        cout << "Modified Duration:" << Modified_Duration << " years." << endl;
        cout << "\n";
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

int calculate_n_terms(int M_year, int M_month, int S_year, int S_month, int interest_frequency)
{
    int year_duration = M_year - S_year;
    int month_duration = year_duration * 12 + (M_month - S_month + 1);
    int coupon_period = 12 / interest_frequency;
    int n_terms = month_duration / coupon_period;
    return n_terms;
}

float calculate_Macaulay_Duration(int n_terms, float bond_price, float coupon, float yield, int interest_frequency)
{
    float Discount = 1, Macaulay_Duration = 0;
    for (int i = 1; i <= n_terms; i++)
	{
		Discount = 1;
		//calculate discount factor
		for (int j = 1; j <= i; j++)
			Discount /= (1 + yield);
		Macaulay_Duration += i * Discount * coupon;
        //consider face value
		if (i == n_terms)
			Macaulay_Duration += n_terms * Discount * FACE_VALUE;
	}
	Macaulay_Duration = Macaulay_Duration / bond_price;
	return Macaulay_Duration / interest_frequency;
}

float calculate_Modified_Duration(float Macaulay_Duration, float yield)
{
    return Macaulay_Duration / (1 + yield);
}
