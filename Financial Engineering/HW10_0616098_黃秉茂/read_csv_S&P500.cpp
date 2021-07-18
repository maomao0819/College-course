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

vector<pair<string, vector<string> > > read_csv(string filename);

int main()
{
    // declaration and initialization
    vector<pair<string, vector<string> > > file_asset = read_csv("S&P 500 Historical Data.csv");
    vector<pair<string, vector<string> > > file_future = read_csv("US 500 Futures Historical Data.csv");
    vector<pair<string, vector<string> > > file_option = read_csv("US 500 Options Historical Data.csv");
    int n_data_assat = file_asset.at(1).second.size();
    for (int data_idx = 0; data_idx < n_data_assat; data_idx++)
    {
        for (int i = 0; i < 7; i++)
        {
            string a = file_asset.at(i).second.at(data_idx);
            cout << a << "\t";
        }
        cout << endl;
    }
    int n_data_future = file_future.at(1).second.size();
    for (int data_idx = 0; data_idx < n_data_future; data_idx++)
    {
        for (int i = 0; i < 7; i++)
        {
            string a = file_future.at(i).second.at(data_idx);
            cout << a << "\t";
        }
        cout << endl;
    }
    int n_data_option = file_option.at(1).second.size();
    for (int data_idx = 0; data_idx < n_data_option; data_idx++)
    {
        for (int i = 0; i < 13; i++)
        {
            string a = file_option.at(i).second.at(data_idx);
            cout << a << "\t";
        }
        cout << endl;
    }
    return 0;
}

vector<pair<string, vector<string> > > read_csv(string filename)
{
    // CAN'T READ UTF-8
    // Reads a CSV file into a vector of <string, vector<string>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, string vector> pairs to store the result
    vector <pair <string, vector<string> > > result;
    // Create an input filestream
    ifstream File(filename.c_str());
    // Make sure the file is open
    if (!File.is_open())
        throw runtime_error("Could not open file");

    // Helper vars
    string line, colname;
    string value;
    int n_col = 0;
    // Read the column names, first line
    if (File.good())
    {
        // Extract the first line in the file
        getline(File, line);
        // Create a stringstream from line
        stringstream ss(line);

        // Extract each column name
        while (getline(ss, colname, ','))
        {
            // Initialize and add <colname, string vector> pairs to result
            result.push_back({colname, vector<string> {}});
            n_col++;
        }
    }
    string exdate;
    // Read data, line by line
    while (getline(File, line))
    {
        // Create a stringstream of the current line
        stringstream ss(line);
        // Keep track of the current column index
        int colIdx = 0;
        // Extract each value
        while (getline(ss, value, ','))
        {
            if (value == "\0")
                value = "-\t";
            result.at(colIdx).second.push_back(value);
            if (colIdx == 2)
                exdate = value;
            colIdx++;

        }
        if (n_col > 7 && exdate != "20200918")
            break;
    }
    // Close file
    File.close();
    return result;
}
