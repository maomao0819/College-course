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
    vector<pair<string, vector<string> > > file = read_csv("TAIEX.csv");
    int n_data = file.at(1).second.size();
    for (int data_idx = 0; data_idx < n_data; data_idx++)
    {
        for (int i = 0; i < 14; i++)
        {
            string a = file.at(i).second.at(data_idx);
            cout << a << "\t";
        }
        cout << endl;
        // int year_maturity = atoi(maturity_date_split[0].c_str());

    }
    return 0;
}

vector<pair<string, vector<string> > > read_csv(string filename)
{
    // Reads a CSV file into a vector of <string, vector<string>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, string vector> pairs to store the result
    vector <pair <string, vector<string> > > result;
    // Create an input filestream
    ifstream myFile(filename.c_str());
    // Make sure the file is open
    if (!myFile.is_open())
        throw runtime_error("Could not open file");

    // Helper vars
    string line, colname;
    string val;
    // Read the column names, first line
    if (myFile.good())
    {
        // Extract the first line in the file
        getline(myFile, line);
        getline(myFile, line);
        // Create a stringstream from line
        stringstream ss(line);
        // Extract each column name
        while (getline(ss, colname, ','))
            // Initialize and add <colname, string vector> pairs to result
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
