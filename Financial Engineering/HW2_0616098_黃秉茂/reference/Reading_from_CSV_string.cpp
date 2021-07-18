#include <string>
#include <fstream>
#include <vector>
#include <utility> // pair
#include <stdexcept> // runtime_error
#include <sstream> // stringstream
#include <iostream>
using namespace std;

vector<pair<string, vector<string> > > read_csv(string filename)
{
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, int vector> pairs to store the result
    vector<pair<string, vector<string> > > result;
    // Create an input filestream
    ifstream myFile(filename.c_str());
    // Make sure the file is open
    if(!myFile.is_open()) throw runtime_error("Could not open file");

    // Helper vars
    string line, colname;
    string val;
    // Read the column names
    if(myFile.good())
    {
        // Extract the first line in the file
        getline(myFile, line);
        // Create a stringstream from line
        stringstream ss(line);
        // Extract each column name
        while(getline(ss, colname, ','))
            // Initialize and add <colname, int vector> pairs to result
            result.push_back({colname, vector<string> {}});
    }
    // Read data, line by line
    while(getline(myFile, line))
    {
        // Create a stringstream of the current line
        stringstream ss(line);
        // Keep track of the current column index
        int colIdx = 0;
        // Extract each value
        while(getline(ss, val, ','))
        {
            result.at(colIdx).second.push_back(val);
            colIdx++;
        }
    }
    // Close file
    myFile.close();
    return result;
}

int main() {
    // Read three_cols.csv and ones.csv
    vector<pair<string, vector<string> > > file = read_csv("issuer_data.csv");
    cout << file.at(1).second.at(3) << endl;
    return 0;
}
