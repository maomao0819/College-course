#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <vector>

using namespace std;

void swap(int& a, int& b);

int main()
{
    ifstream in_s;
    ofstream out_s;
    in_s.open("input.txt");
    out_s.open("output.txt");
    vector <int> dataset;
    vector <int> dataset_for_fisrt_line;
    int data = 0;
    int course = 0;
    int study_day = 0;
    string first_line;
    getline(in_s, first_line);
    stringstream ss_token(first_line);
    string data_token;
    while(ss_token >> data_token)
        dataset_for_fisrt_line.push_back(atoi(data_token.c_str()));
    ss_token.clear();
    course = dataset_for_fisrt_line.size();
    bool end = false;
    while(!end)
    {
        vector<int>::iterator it;
        for(it = dataset_for_fisrt_line.begin(); it != dataset_for_fisrt_line.end(); it++)
            dataset.push_back(*it);
        study_day = 0;
        bool data_check  = true;
        while(data_check)
        {
            data_check = false;
            string table_data;
            getline(in_s, table_data);
            stringstream ss_token(table_data);
            while(ss_token >> data_token)
            {
                dataset.push_back(atoi(data_token.c_str()));
                data_check = true;
            }
            ss_token.clear();
            study_day++;
        }
        data = dataset.size();
        int table[course + 1][course + study_day + 1];
        for(int i = 0; i < course + 1; i++)
            for(int j = 0; j < course + study_day + 1; j++)
                table[i][j] = 0;
        it = dataset.begin();
        for(int i = 0; i < study_day; i++)
        {
            for(int j = 0; j < course; j++)
            {
                table[j][i] = *it;
                it++;
            }
        }
        int arg = 1;
        while(arg == 1)
        {
            end = true;
            dataset_for_fisrt_line.clear();
            arg = 0;
            int days = 0;
            string argument;
            getline(in_s, argument);
            stringstream ss_token(argument);
            while(ss_token >> data_token)
            {
                dataset_for_fisrt_line.push_back(atoi(data_token.c_str()));
                end = false;
            }
            ss_token.clear();
            arg = dataset_for_fisrt_line.size();
            if(arg > 1)
                course = arg;
            else if(arg == 1)
            {
                string empty_line;
                getline(in_s, empty_line);
                days = dataset_for_fisrt_line.front();
                int profitTable[course + 1][days + 1];
                for(int i = 0; i < course + 1; i++)
                    for(int j = 0; j < days + 1; j++)
                        profitTable[i][j] = 0;
                for(int i = 0; i < study_day; i++)
                    profitTable[0][i] = table[0][i];
                for(int i = 1; i < course; i++)
                {
                    for(int j = 0; j < study_day; j++)
                        for(int k = (i + j) - 1; k >= 0; k--)
                            if(profitTable[i - 1][k] + table[i][(i + j) - k - 1] > profitTable[i][i + j])
                                profitTable[i][i + j] = profitTable[i - 1][k] + table[i][(i + j) - k - 1];
                }
                /*for(int i = 0; i < course + 1; i++)
                {
                    for(int j = 0; j < days + 1; j++)
                    {
                        cout << profitTable[i][j] << " ";
                    }
                    cout << endl;
                }*/
                int max = profitTable[course - 1][days - 1];
                cout << max << endl;
                out_s << max << endl;
            }
        }
    }
    in_s.close();
    out_s.close();
    return 0;
}

void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}
