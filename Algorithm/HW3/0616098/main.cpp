#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

using namespace std;

int max(int a, int b);

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
    // get the line info
    string first_line;
    getline(in_s, first_line);
    stringstream ss_token(first_line);
    string data_token;
    // get first line info and the number of course
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
        // get the value and the scope of the table
        while(data_check)
        {
            data_check = false;
            // get the line info
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
        int std_table[course][study_day];
        for(int i = 0; i < course; i++)
            for(int j = 0; j < study_day; j++)
                std_table[i][j] = 0;
        it = dataset.begin();
        // set-up the base table
        for(int i = 0; i < study_day; i++)
        {
            for(int j = 0; j < course; j++)
            {
                std_table[j][i] = *it;
                it++;
            }
        }
        int arg = 1;
        // next table or answer the max score with input
        while(arg == 1)
        {
            end = true;
            dataset_for_fisrt_line.clear();
            arg = 0;
            int days = 0;
            // get the line info
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
            // next table
            if(arg > 1)
                course = arg;
            // input "days"
            else if(arg == 1)
            {
                string empty_line;
                getline(in_s, empty_line);
                days = dataset_for_fisrt_line.front();
                int profitTable[course + 1][days + 1];
                for(int i = 0; i <= course; i++)
                    for(int j = 0; j <= days; j++)
                        profitTable[i][j] = 0;
                // set-up more useful table
                for(int i = 1; i <= course; i++)
                {
                    for(int j = 1; j <= days; j++)
                    {
                        if(j - 1 < study_day)
                            profitTable[i][j] = std_table[i - 1][j - 1];
                        else
                            profitTable[i][j] = std_table[i - 1][study_day - 1];
                    }
                }
                int dp[max(days, (course + 1) * (study_day + 1))];
                memset(dp, 0, sizeof(dp));
                // grouping_knapsack_problem
                for(int i = 1; i <= course; i++)
                    for(int j = days; j >= 0; j--)
                        for(int k = 1; k <= days; k++)
                            if(j - k >= 0)
                                dp[j] = max(dp[j], dp[j - k] + profitTable[i][k]);
                int ans = dp[days];
                cout << ans << endl;
                out_s << ans << endl;
            }
        }
    }
    in_s.close();
    out_s.close();
    return 0;
}

int max(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}
