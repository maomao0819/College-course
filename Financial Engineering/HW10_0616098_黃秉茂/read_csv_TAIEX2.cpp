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

int n_col = 1;

vector <pair <string, vector <pair <string, vector<string> > > > > read_csv(string filename);

int main()
{
    // declaration and initialization
    vector <pair <string, vector <pair <string, vector<string> > > > > file = read_csv("TAIEX.csv");
    int n_data = file.at(1).second.at(1).second.size();
    for (int data_idx = 0; data_idx < n_data; data_idx++)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < n_col / 2; j++)
            {
                string a = file.at(i).second.at(j).second.at(data_idx);
                cout << a << "\t";
            }
        }
        cout << endl;
        // int year_maturity = atoi(maturity_date_split[0].c_str());

    }
    return 0;
}

vector <pair <string, vector <pair <string, vector<string> > > > > read_csv(string filename)
{
    // Reads a CSV file into a vector of <string, vector<string>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, string vector> pairs to store the result
    vector <pair <string, vector <pair <string, vector<string> > > > > result;
    vector <pair <string, vector<string> > > result2;
    // Create an input filestream
    ifstream File(filename.c_str());
    // Make sure the file is open
    if (!File.is_open())
        throw runtime_error("Could not open file");

    // Helper vars
    string line, type, colname;

    // Read the column names, first line
    if (File.good())
    {
        // Extract the first line in the file
        getline(File, line);
        stringstream ss_type(line);
        while (getline(ss_type, type, ','))
        {
            if (type != "\0")
                result.push_back({type, result2});
            n_col++;
        }
        getline(File, line);
        // Create a stringstream from line
        stringstream ss_col(line);
        // Extract each column name
        int col_idx = 0;
        while (getline(ss_col, colname, ','))
        {
            // Initialize and add <colname, string vector> pairs to result
            result.at(col_idx / (n_col / 2)).second.push_back({colname, vector<string> {}});
            col_idx++;
        }

    }
    // Read data, line by line
    while (getline(File, line))
    {
        string value;
        // Create a stringstream of the current line
        stringstream ss(line);
        // Keep track of the current column index
        int col_idx = 0;
        // Extract each value
        while (getline(ss, value, ','))
        {
            result.at(col_idx / (n_col / 2)).second.at(col_idx % (n_col / 2)).second.push_back(value);
            col_idx++;
        }
    }
    // Close file
    File.close();
    return result;
}
