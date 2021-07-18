// 3295 and 3300 has arbitrage opportunity

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

#define DAY / 360
float interest_rate = 0.0009; // https://www.statista.com/statistics/187616/effective-rate-of-us-federal-funds-monthly/
float year_duration = 10.0 DAY;
bool base_bid_ask_checked = false;
bool call_check = true;
bool put_check = true;
bool bool_check_future = false;
bool two_strike_call = true;
bool two_strike_put = true;
vector <pair <string, vector<string> > > read_csv(string filename);

float PV(float value);
float FV(float value);
void print_arbitrage_opportunity(string str);
void print_profit(float value);
void print_transaction_cost(float value);
bool check_bid_ask(float asset_bid, float asset_ask, float future_bid, float future_ask, float call_option_bid, float call_option_ask, float put_option_bid, float put_option_ask);
bool check_future(float asset_bid, float asset_ask, float future_bid, float future_ask);
bool put_call_parity(float asset_bid, float asset_ask, float call_option_bid, float call_option_ask, float put_option_bid, float put_option_ask, float strike_price);
bool check_option_with_strike_price(float call_option_bid_1, float call_option_bid_2, float call_option_ask_1, float call_option_ask_2,
                                    float put_option_bid_1, float put_option_bid_2, float put_option_ask_1, float put_option_ask_2, float strike_price_1 , float strike_price_2);
bool check_put_option_upper_bound(int option_type, float put_option_bid, float strike_price);
bool check_option_upper_bond(int option_type, float asset_ask, float call_option_bid, float put_option_bid, float strike_price);
bool check_call_option_lower_bound(float asset_bid, float call_option_ask, float strike_price);
bool check_put_option_lower_bound(int option_type, float asset_ask, float put_option_ask, float strike_price);
bool check_option_lower_bound(int option_type, float asset_bid, float asset_ask, float call_option_ask, float put_option_ask, float strike_price);
bool check_convexity(int option_way, float option_bid_middle, float option_ask_low, float option_ask_high,
                     float strike_price_low, float strike_price_middle, float strike_price_high);
bool check_convexity_order(int option_way, float option_bid_1, float option_bid_2, float option_bid_3,
                           float option_ask_1, float option_ask_2, float option_ask_3,
                           float strike_price_1, float strike_price_2, float strike_price_3);
bool check_future_and_option(float asset_bid, float asset_ask, float future_bid, float future_ask,
                             float call_option_bid, float call_option_ask, float put_option_bid, float put_option_ask, float strike_price);
bool check_arbitrage_no_strike_price(float asset_bid, float asset_ask, float future_bid, float future_ask,
                                     float call_option_bid, float call_option_ask, float put_option_bid, float put_option_ask);
bool check_arbitrage_one_strike_price(int option_type, float asset_bid, float asset_ask, float future_bid, float future_ask,
                                      float call_option_bid, float call_option_ask, float put_option_bid, float put_option_ask, float strike_price);

int main()
{
    bool volume_check = true;
    // volume_check: only consider option which the number of which is more than one.

    // declaration and initialization
    vector<pair<string, vector<string> > > file_asset = read_csv("S&P 500 Historical Data.csv");
    vector<pair<string, vector<string> > > file_future = read_csv("US 500 Futures Historical Data.csv");
    vector<pair<string, vector<string> > > file_option = read_csv("US 500 Options Historical Data.csv");
    // file.at(option_type).second.at(column).second.at(data_idx);

    int n_data = file_option.at(1).second.size() - 1;

    float asset_bid = float(floor(atof(file_asset.at(1).second.at(0).c_str())));
    float asset_ask = float(ceil(atof(file_asset.at(1).second.at(0).c_str())));
    float future_bid = float(floor(atof(file_future.at(1).second.at(0).c_str())));
    float future_ask = float(ceil(atof(file_future.at(1).second.at(0).c_str())));
    string date = file_option.at(1).second.at(1);
    string exdate = file_option.at(2).second.at(1);
    string dot_line(50, '-');
    cout << "<<<" << dot_line << "   S&P 500   " << dot_line << ">>>\n";
    cout << "INTEREST RATE = " << interest_rate << "\t\tMATURITY = 10 DAY" << "\t\tDATE: " << date << "\t\t\tEXDATE: " << exdate << "\n";
    cout << "S&P 500's BID = " << asset_bid << "\t\t" << "S&P 500's ASK = " << asset_ask << "\t\t";
    cout << "FUTURE's BID = " << future_bid << "\t\t" << "FUTURE's ASK = " << future_ask << "\n";
    n_data /= 2;
    float strike_price [n_data] = {};
    float call_option_bid [n_data] = {};
    float call_option_ask [n_data] = {};
    float put_option_bid [n_data] = {};
    float put_option_ask [n_data] = {};
    int call_option_volume [n_data] = {};
    int put_option_volume [n_data] = {};

    // 1: European  2: American
    int option_type = 0;
    if (file_option.at(12).second.at(2) == "E")
        option_type = 1;
    else if (file_option.at(12).second.at(2) == "A")
        option_type = 2;

    for (int data_idx = 0; data_idx < n_data; data_idx++)
    {
        strike_price[data_idx] = atof(file_option.at(5).second.at(data_idx).c_str()) / 1000;
        call_option_bid[data_idx] = atof(file_option.at(6).second.at(data_idx).c_str());
        call_option_ask[data_idx] = atof(file_option.at(7).second.at(data_idx).c_str());
        call_option_volume[data_idx] = atoi(file_option.at(8).second.at(data_idx).c_str());
        put_option_bid[data_idx] = atof(file_option.at(6).second.at(data_idx + n_data).c_str());
        put_option_ask[data_idx] = atof(file_option.at(7).second.at(data_idx + n_data).c_str());
        put_option_volume[data_idx] = atoi(file_option.at(8).second.at(data_idx + n_data).c_str());
    }

    cout << "EXCERCISE STYLE : ";
    if (option_type == 1)
        cout << "European\t";
    else if (option_type == 2)
        cout << "American\t";
    cout << "VOLUME CHECK: " << volume_check << endl;
    cout << "\t\t\t\tCALL OPTION\t\t\tPUT OPTION\n";
    cout << "STRIKE PRICE\tVOLUME\t\tBEST BID\tBEST OFFER\tBEST BID\tBEST OFFER\n";
    for (int data_idx = 0; data_idx < n_data; data_idx++)
    {
        cout << strike_price[data_idx] << "\t\t";
        cout << call_option_volume[data_idx] << "\t\t";
        cout << call_option_bid[data_idx] << "\t\t";
        cout << call_option_ask[data_idx] << "\t\t";
        cout << put_option_bid[data_idx] << "\t\t";
        cout << put_option_ask[data_idx] << "\n";
    }

    string dot_line2(10, '-');
    cout << "\n\n<" << dot_line2 << "   WHEN NO CONSIDER STRIKE PRICE.   " << dot_line2 << ">\n";
    base_bid_ask_checked = false;
    bool arbitrage_no_strike = false;
    for (int data_idx = 0; data_idx < n_data; data_idx++)
    {
        bool cond_call_volume = call_option_volume[data_idx] > 0;
        bool cond_put_volume = put_option_volume[data_idx] > 0;
        if (volume_check && (cond_call_volume == false && cond_put_volume == false))
            continue;
        bool cond_call_price = (call_option_bid[data_idx] && call_option_ask[data_idx]);
        bool cond_put_price = (put_option_bid[data_idx] && put_option_ask[data_idx]);
        call_check = cond_call_price;
        put_check = cond_put_price;
        if (volume_check)
        {
            call_check = call_check && cond_call_volume;
            put_check = put_check && cond_put_volume;
        }
        if (cond_call_price || cond_put_price)
        {
            bool check = check_arbitrage_no_strike_price(asset_bid, asset_ask, future_bid, future_ask,
                                                         call_option_bid[data_idx], call_option_ask[data_idx],
                                                         put_option_bid[data_idx], put_option_ask[data_idx]);
            base_bid_ask_checked = true;
            if (check)
                arbitrage_no_strike = true;
        }
        else
        {
            if (cond_call_price == false)
                cout << "Some of the call option data is missing when the strike price is " << strike_price[data_idx] << ".\n";
            if (cond_put_price == false)
                cout << "Some of the put option data is missing the strike price is " << strike_price[data_idx] << ".\n";
        }
    }
    if (arbitrage_no_strike == false)
        cout << "There\'s no any arbitrage opportunity on bid and ask price.";
    cout << "\n\n\n\n";

    cout << dot_line2 << "   WHEN ONLY CONSIDER ONE STRIKE PRICE.   " << dot_line2 << ">\n";
    for (int data_idx = 0; data_idx < n_data; data_idx++)
    {
        bool cond_call_volume = call_option_volume[data_idx] > 0;
        bool cond_put_volume = put_option_volume[data_idx] > 0;
        if (volume_check && (cond_call_volume == false && cond_put_volume == false))
            continue;
        cout << "When the strike price is " << strike_price[data_idx] << ".\n";
        bool cond_call_price = (call_option_bid[data_idx] || call_option_ask[data_idx]);
        bool cond_put_price = (put_option_bid[data_idx] || put_option_ask[data_idx]);
        call_check = cond_call_price;
        put_check = cond_put_price;
        if (volume_check)
        {
            call_check = call_check && cond_call_volume;
            put_check = put_check && cond_put_volume;
        }

        if (cond_call_price || cond_put_price)
            check_arbitrage_one_strike_price(option_type, asset_bid, asset_ask, future_bid, future_ask,
                                             call_option_bid[data_idx], call_option_ask[data_idx],
                                             put_option_bid[data_idx], put_option_ask[data_idx],
                                             strike_price[data_idx]);
        else
        {
            if (cond_call_price == false)
                cout << "Some of the call option data is missing.\n";
            if (cond_put_price == false)
                cout << "Some of the put option data is missing.\n";
        }
        cout << "\n\n";
    }

    cout << "\n<" << dot_line2 << "   WHEN CONSIDER 2 STRIKE PRICEs.   " << dot_line2 << ">\n";
    bool arbitrage_two_strike = false;
    for (int data_idx_1 = 0; data_idx_1 < n_data; data_idx_1++)
    {
        bool cond_call_volume1 = call_option_volume[data_idx_1] > 0;
        bool cond_put_volume1 = put_option_volume[data_idx_1] > 0;
        if (volume_check && (cond_call_volume1 == false && cond_put_volume1 == false))
            continue;
        for (int data_idx_2 = data_idx_1 + 1; data_idx_2 < n_data; data_idx_2++)
        {
            bool cond_call_volume2 = call_option_volume[data_idx_2] > 0;
            bool cond_put_volume2 = put_option_volume[data_idx_2] > 0;
            if (volume_check && (cond_call_volume2 == false && cond_put_volume2 == false))
                continue;

            bool cond_call_price1 = (call_option_bid[data_idx_1] || call_option_ask[data_idx_1]);
            bool cond_put_price1 = (put_option_bid[data_idx_1] || put_option_ask[data_idx_1]);
            bool cond_call_price2 = (call_option_bid[data_idx_2] || call_option_ask[data_idx_2]);
            bool cond_put_price2 = (put_option_bid[data_idx_2] || put_option_ask[data_idx_2]);

            two_strike_call = cond_call_price1 && cond_call_price2;
            two_strike_put = cond_put_price1 && cond_put_price2;

            if (volume_check)
            {
                two_strike_call = cond_call_volume1 && cond_call_volume2;
                two_strike_put = cond_put_volume1 && cond_put_volume2;
            }

            bool check = check_option_with_strike_price(call_option_bid[data_idx_1], call_option_bid[data_idx_2], call_option_ask[data_idx_1], call_option_ask[data_idx_2],
                                                        put_option_bid[data_idx_1], put_option_bid[data_idx_2], put_option_ask[data_idx_1], put_option_ask[data_idx_2],
                                                        strike_price[data_idx_1] , strike_price[data_idx_2]);
            if (check)
                arbitrage_two_strike = true;
        }
    }
    if (arbitrage_two_strike == false)
        cout << "There\'s no any arbitrage opportunity.";
    cout << "\n\n\n\n";

    cout << "<" << dot_line2 << "   WHEN CONSIDER 3 STRIKE PRICEs.   " << dot_line2 << ">\n";
    bool arbitrage_three_strike = false;
    for (int data_idx_1 = 0; data_idx_1 < n_data; data_idx_1++)
    {
        bool cond_call_volume1 = call_option_volume[data_idx_1] > 0;
        bool cond_put_volume1 = put_option_volume[data_idx_1] > 0;
        if (volume_check && (cond_call_volume1 == false && cond_put_volume1 == false))
            continue;
        for (int data_idx_2 = data_idx_1 + 1; data_idx_2 < n_data; data_idx_2++)
        {
            bool cond_call_volume2 = call_option_volume[data_idx_2] > 0;
            bool cond_put_volume2 = put_option_volume[data_idx_2] > 0;
            if (volume_check && (cond_call_volume2 == false && cond_put_volume2 == false))
                continue;
            for (int data_idx_3 = data_idx_2 + 1; data_idx_3 < n_data; data_idx_3++)
            {
                bool cond_call_volume3 = call_option_volume[data_idx_3] > 0;
                bool cond_put_volume3 = put_option_volume[data_idx_3] > 0;
                if (volume_check && (cond_call_volume3 == false && cond_put_volume3 == false))
                    continue;
                bool cond_call_price1 = (call_option_bid[data_idx_1] || call_option_ask[data_idx_1]);
                bool cond_put_price1 = (put_option_bid[data_idx_1] || put_option_ask[data_idx_1]);
                bool cond_call_price2 = (call_option_bid[data_idx_2] || call_option_ask[data_idx_2]);
                bool cond_put_price2 = (put_option_bid[data_idx_2] || put_option_ask[data_idx_2]);
                bool cond_call_price3 = (call_option_bid[data_idx_3] || call_option_ask[data_idx_3]);
                bool cond_put_price3 = (put_option_bid[data_idx_3] || put_option_ask[data_idx_3]);

                bool cond_call = cond_call_price1 && cond_call_price2 && cond_call_price3;
                bool cond_put = cond_put_price1 && cond_put_price2 && cond_put_price3;
                if (volume_check)
                {
                    cond_call = cond_call && cond_call_volume1 && cond_call_volume2 && cond_call_volume3;
                    cond_put = cond_put && cond_put_volume1 && cond_put_volume2 && cond_put_volume3;
                }

                bool check1 = false;
                if (cond_call)
                    check1 = check_convexity_order(1, call_option_bid[data_idx_1], call_option_bid[data_idx_2], call_option_bid[data_idx_3],
                                                   call_option_ask[data_idx_1], call_option_ask[data_idx_2], call_option_ask[data_idx_3],
                                                   strike_price[data_idx_1] , strike_price[data_idx_2], strike_price[data_idx_3]);
                bool check2 = false;
                if (cond_put)
                    check2 = check_convexity_order(2, put_option_bid[data_idx_1], put_option_bid[data_idx_2], put_option_bid[data_idx_3],
                                                   put_option_ask[data_idx_1], put_option_ask[data_idx_2], put_option_ask[data_idx_3],
                                                   strike_price[data_idx_1] , strike_price[data_idx_2], strike_price[data_idx_3]);
                if (check1 || check2)
                    arbitrage_three_strike = true;
            }
        }
    }
    if (arbitrage_three_strike == false)
        cout << "There\'s no any arbitrage opportunity on convexity.";
    cout << "\n";
    return 0;
}

vector <pair <string, vector<string> > > read_csv(string filename)
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

float PV(float value)
{
    return value * exp(-1.0 * interest_rate * year_duration);
}

float FV(float value)
{
    return value * exp(interest_rate * year_duration);
}

void print_arbitrage_opportunity(string str)
{
    cout << "-----------------------------------------------------------------------\n";
    cout << "Arbitrage opportunity on the " << str << ".\n";
    cout << "You have an arbitrage opportunity with initially ";
    return;
}

void print_profit(float value)
{
    cout << "And the profit with the arbitrage strategy is: " << value << ".\n";
    return;
}

void print_transaction_cost(float value)
{
    cout << " - " << value << " (transaction cost)\n";
    return;
}

bool check_bid_ask(float asset_bid, float asset_ask, float future_bid, float future_ask, float call_option_bid, float call_option_ask, float put_option_bid, float put_option_ask)
{
    float transaction_cost = 1.0 + 1.0;
    bool check = false;
    if (base_bid_ask_checked == false && (asset_bid - asset_ask > transaction_cost))
    {
        print_arbitrage_opportunity("Bid-Ask");
        cout << "You have an arbitrage opportunity with buying an underlying asset at " << asset_ask;
        cout << " and selling an underlying asset at " << asset_bid << ".\n";
        print_profit((asset_bid - asset_ask) - transaction_cost);
        cout << (asset_bid - asset_ask) - transaction_cost << " = (" << asset_bid << " - " << asset_ask << ")";
        print_transaction_cost(transaction_cost);
        check = true;
    }
    if (base_bid_ask_checked == false && (future_bid - future_bid > transaction_cost))
    {
        print_arbitrage_opportunity("Bid-Ask");
        cout << "buying a future at " << future_ask;
        cout << " and selling a future at " << future_bid << ".\n";
        print_profit((future_bid - future_ask) - transaction_cost);
        cout << (future_bid - future_ask) - transaction_cost << " = (" << future_bid << " - " << future_ask << ")";
        print_transaction_cost(transaction_cost);
        check = true;
    }
    if (call_check && (call_option_bid - call_option_bid > transaction_cost))
    {
        print_arbitrage_opportunity("Bid-Ask");
        cout << "buying a call option at " << call_option_ask;
        cout << " and selling a call option at " << call_option_bid << ".\n";
        print_profit((call_option_bid - call_option_ask) - transaction_cost);
        cout << (call_option_bid - call_option_ask) - transaction_cost << " = (" << call_option_bid << " - " << call_option_ask << ")";
        print_transaction_cost(transaction_cost);
        check = true;
    }
    if (put_check && (put_option_bid - put_option_bid > transaction_cost))
    {
        print_arbitrage_opportunity("Bid-Ask");
        cout << "buying a put option at " << put_option_ask;
        cout << " and selling a put option at " << put_option_bid << ".\n";
        print_profit((put_option_bid - put_option_ask) - transaction_cost);
        cout << (put_option_bid - put_option_ask) - transaction_cost << " = (" << put_option_bid << " - " << put_option_ask << ")";
        print_transaction_cost(transaction_cost);
        check = true;
    }
    return check;
}

bool check_future(float asset_bid, float asset_ask, float future_bid, float future_ask)
{
    if (bool_check_future)
        return false;
    float transaction_cost = 1.0 + 1.0;
    /*if (PV(future_bid) - asset_ask > transaction_cost)
    {
        print_arbitrage_opportunity("future");
        cout << "Arbitrage opportunity on the future.\n";
        cout << "borrowing money " << asset_ask;
        cout << ", buying an underlying asset at " << asset_ask;
        cout << ", and shorting a future at " << future_bid << ".\n";
        print_profit((PV(future_bid) - asset_ask) - transaction_cost);
        cout << (PV(future_bid) - asset_ask) - transaction_cost << " = (" << PV(future_bid) << " - " << asset_ask << ")";
        print_transaction_cost(transaction_cost);
        return true;
    }
    else if (asset_bid - PV(future_ask) > transaction_cost)
    {
        print_arbitrage_opportunity("future");
        cout << "saving money " << asset_bid;
        cout << ", longing a future at " << future_ask;
        cout << ", and shorting an underlying asset at " << asset_bid << ".\n";
        print_profit((asset_bid - PV(future_ask)) - transaction_cost);
        cout << (asset_bid - PV(future_ask)) - transaction_cost << " = (" << asset_bid << " - " << PV(future_ask) << ")";
        print_transaction_cost(transaction_cost);
        return true;
    }*/
    if (future_bid - asset_ask > transaction_cost)
    {
        print_arbitrage_opportunity("future");
        cout << "buying an underlying asset at " << asset_ask;
        cout << " and selling a future at " << future_bid << ".\n";
        print_profit((future_bid - asset_ask) - transaction_cost);
        cout << (future_bid - asset_ask) - transaction_cost << " = (" << future_bid << " - " << asset_ask << ")";
        print_transaction_cost(transaction_cost);
        bool_check_future = true;
        return true;
    }
    else if (asset_bid - future_ask > transaction_cost)
    {
        print_arbitrage_opportunity("future");
        cout << "buying a future at " << future_ask;
        cout << " and selling an underlying asset at " << asset_bid << ".\n";
        print_profit((asset_bid - future_ask) - transaction_cost);
        cout << (asset_bid - future_ask) - transaction_cost << " = (" << asset_bid << " - " << future_ask << ")";
        print_transaction_cost(transaction_cost);
        bool_check_future = true;
        return true;
    }
    return false;
}

bool put_call_parity(float asset_bid, float asset_ask, float call_option_bid, float call_option_ask, float put_option_bid, float put_option_ask, float strike_price)
{
    if (call_check && put_check == false)
        return false;
    float transaction_cost = 1.0 + 1.0 + 1.0;
    if ((put_option_bid + asset_bid) - (call_option_ask + PV(strike_price)) > transaction_cost)
    {
        print_arbitrage_opportunity("Put-Call Parity");
        cout << "buying a call option at " << call_option_ask;
        // cout << " and a zero bond at present value of strike price " << strike_price << " at " << PV(strike_price);
        cout << ", saving at present value of strike price " << strike_price << " at " << PV(strike_price);
        cout << ", and selling a put option at " << put_option_bid;
        cout << " and an underlying asset at " << asset_bid << ".\n";
        print_profit((put_option_bid + asset_bid) - (call_option_ask + PV(strike_price)) - transaction_cost);
        cout << (put_option_bid + asset_bid) - (call_option_ask + PV(strike_price)) - transaction_cost << " = (";
        cout << put_option_bid << " + " << asset_bid << ") - (" << call_option_ask << " + " << PV(strike_price) << ")";
        print_transaction_cost(transaction_cost);
        return true;
    }
    else if ((call_option_bid + PV(strike_price)) - (put_option_ask + asset_ask) > transaction_cost)
    {
        print_arbitrage_opportunity("Put-Call Parity");
        cout << "buying a put option at " << put_option_ask;
        cout << " and an underlying asset at " << asset_ask ;
        cout << ", selling a call option at " << call_option_bid;
        // cout << " and a zero bond at present value of strike price " << strike_price << " at " << PV(strike_price) << ".\n";
        cout << ", and borrowing at present value of strike price " << strike_price << " at " << PV(strike_price) << ".\n";
        print_profit((call_option_bid + PV(strike_price)) - (put_option_ask + asset_ask) - transaction_cost);
        cout << (call_option_bid + PV(strike_price)) - (put_option_ask + asset_ask) - transaction_cost << " = (";
        cout << call_option_bid << " + " << PV(strike_price) << ") - (" << put_option_ask << " + " << asset_ask << ")";
        print_transaction_cost(transaction_cost);
        return true;
    }
    return false;
}

bool check_option_with_strike_price(float call_option_bid_1, float call_option_bid_2, float call_option_ask_1, float call_option_ask_2,
                                    float put_option_bid_1, float put_option_bid_2, float put_option_ask_1, float put_option_ask_2, float strike_price_1 , float strike_price_2)
{
    if (two_strike_call == false && two_strike_put == false)
        return false;
    float call_option_bid_high = call_option_bid_1;
    float call_option_ask_low = call_option_ask_2;
    float put_option_bid_low = put_option_bid_2;
    float put_option_ask_high = put_option_bid_1;
    float strike_price_high = strike_price_1;
    float strike_price_low = strike_price_2;
    bool check = false;
    if (strike_price_1 < strike_price_2)
    {
        call_option_bid_high = call_option_bid_2;
        call_option_ask_low = call_option_ask_1;
        put_option_bid_low = put_option_bid_1;
        put_option_ask_high = put_option_bid_2;
        strike_price_high = strike_price_2;
        strike_price_low = strike_price_1;
    }
    float transaction_cost = 1.0 + 1.0;
    if (two_strike_call && (call_option_bid_high - call_option_ask_low > transaction_cost))
    {
        print_arbitrage_opportunity("call option with different strike prices");
        cout << "buying a call option with strike price " << strike_price_low;
        cout << " at " << call_option_ask_low;
        cout << " and selling a call option with strike price " << strike_price_high;
        cout << " at " << call_option_bid_high << ".\n";
        print_profit((call_option_bid_high - call_option_ask_low) - transaction_cost);
        cout << (call_option_bid_high - call_option_ask_low) - transaction_cost << " = (";
        cout << call_option_bid_high << " - " << call_option_ask_low << ")";
        print_transaction_cost(transaction_cost);
        check = true;
    }
    if (two_strike_put && (put_option_bid_low - put_option_ask_high > transaction_cost))
    {
        print_arbitrage_opportunity("call option with different strike prices");
        cout << "buying a put option with strike price " << strike_price_high;
        cout << " at " << put_option_ask_high;
        cout << " and selling a put option with strike price " << strike_price_low;
        cout << " at " << put_option_bid_low << ".\n";
        print_profit((put_option_bid_low - put_option_ask_high) - transaction_cost);
        cout << (put_option_bid_low - put_option_ask_high) - transaction_cost << " = (";
        cout << put_option_bid_low << " - " << put_option_ask_high << ")";
        print_transaction_cost(transaction_cost);
        check = true;
    }
    return check;
}

bool check_call_option_upper_bound(float asset_ask, float call_option_bid)
{
    float transaction_cost = 1.0 + 1.0;
    if (call_option_bid - asset_ask > transaction_cost)
    {
        print_arbitrage_opportunity("call option upper bound");
        cout << "selling a call option at " << call_option_bid;
        cout << " and buying an underlying asset at " << asset_ask << ".\n";
        print_profit((call_option_bid - asset_ask) - transaction_cost);
        cout << (call_option_bid - asset_ask) - transaction_cost << " = (";
        cout << call_option_bid << " - " << asset_ask << ")";
        print_transaction_cost(transaction_cost);
        return true;
    }
    return false;
}

bool check_put_option_upper_bound(int option_type, float put_option_bid, float strike_price)
{
    if (option_type == 1)
    {
        float transaction_cost = 1.0;
        if (put_option_bid - PV(strike_price) > transaction_cost)
        {
            print_arbitrage_opportunity("European put option upper bound");
            cout << "selling a put option at " << put_option_bid << ".\n";
            print_profit((put_option_bid - PV(strike_price)) - transaction_cost);
            cout << (put_option_bid - PV(strike_price)) - transaction_cost << " = (";
            cout << put_option_bid << " - " << PV(strike_price) << ")";
            print_transaction_cost(transaction_cost);
            return true;
        }
    }
    else if (option_type == 2)
    {
        float transaction_cost = 1.0;
        if (put_option_bid - strike_price > transaction_cost)
        {
            print_arbitrage_opportunity("American put option upper bound");
            cout << "with selling a put option at " << put_option_bid << ".\n";
            print_profit((put_option_bid - strike_price) - transaction_cost);
            cout << (put_option_bid - strike_price) - transaction_cost << " = (";
            cout << put_option_bid << " - " << strike_price << ")";
            print_transaction_cost(transaction_cost);
            return true;
        }
    }
    return false;
}

bool check_option_upper_bond(int option_type, float asset_ask, float call_option_bid, float put_option_bid, float strike_price)
{
    bool arbitrage_opportunity_1 = false;
    if (call_check)
        arbitrage_opportunity_1 = check_call_option_upper_bound(asset_ask, call_option_bid);
    bool arbitrage_opportunity_2 = false;
    if (put_check)
        arbitrage_opportunity_2 = check_put_option_upper_bound(option_type, put_option_bid, strike_price);
    return arbitrage_opportunity_1 | arbitrage_opportunity_2;
}

bool check_call_option_lower_bound(float asset_bid, float call_option_ask, float strike_price)
{
    float transaction_cost_1 = 1.0;
    bool check = false;
    if (call_option_ask < -transaction_cost_1)
    {
        print_arbitrage_opportunity("call option lower bound");
        cout << "with buying a call option at " << call_option_ask << ".\n";
        print_profit((-call_option_ask) - transaction_cost_1);
        cout << (-call_option_ask) - transaction_cost_1 << " = (";
        cout << " (-" << call_option_ask << ")";
        print_transaction_cost(transaction_cost_1);
        check = true;
    }
    float transaction_cost_2 = 1.0 + 1.0;
    if (asset_bid - (call_option_ask + PV(strike_price)) > transaction_cost_2)
    {
        print_arbitrage_opportunity("call option lower bound");
        cout << "buying a call option at " << call_option_ask;
        // cout << " and a zero bond at present value of strike price " << strike_price << " at " << PV(strike_price);
        cout << ", saving at present value of strike price " << strike_price << " at " << PV(strike_price);
        cout << ", and selling an underlying asset at " << asset_bid << ".\n";
        print_profit((asset_bid - (call_option_ask + PV(strike_price))) - transaction_cost_2);
        cout << (asset_bid - (call_option_ask + PV(strike_price))) - transaction_cost_2 << " = (";
        cout << asset_bid << " - (" << call_option_ask << " + " << PV(strike_price) << "))";
        print_transaction_cost(transaction_cost_2);
        check = true;
    }
    return check;
}

bool check_put_option_lower_bound(int option_type, float asset_ask, float put_option_ask, float strike_price)
{
    float transaction_cost = 1.0;
    bool check = false;
    if (put_option_ask < -transaction_cost)
    {
        print_arbitrage_opportunity("put option lower bound");
        cout << "buying a put option at " << put_option_ask << ".\n";
        print_profit((-put_option_ask) - transaction_cost);
        cout << (-put_option_ask) - transaction_cost << " = (";
        cout << " (-" << put_option_ask << ")";
        print_transaction_cost(transaction_cost);
        check = true;
    }
    if (option_type == 1)
    {
        transaction_cost = 1.0 + 1.0 + 1.0;
        if ((PV(strike_price)) - (put_option_ask + asset_ask) > transaction_cost)
        {
            print_arbitrage_opportunity("European put option lower bound");
            cout << "Arbitrage opportunity on the Put-Call Parity.\n";
            cout << "buying a put option at " << put_option_ask;
            cout << " and an underlying asset at " << asset_ask ;
            cout << ", selling a call option";
            // cout << " and a zero bond at present value of strike price " << strike_price << " at " << PV(strike_price) << ".\n";
            cout << ", and borrowing at present value of strike price " << strike_price << " at " << PV(strike_price) << ".\n";
            print_profit(((PV(strike_price)) - (put_option_ask + asset_ask)) - transaction_cost);
            cout << ((PV(strike_price)) - (put_option_ask + asset_ask)) - transaction_cost << " = ((";
            cout << PV(strike_price) << ") - (" << put_option_ask << " + " << asset_ask << "))";
            print_transaction_cost(transaction_cost);
            check = true;
        }
    }
    else if (option_type == 2)
    {
        transaction_cost = 1.0;
        if ((strike_price - asset_ask) - put_option_ask > transaction_cost)
        {
            print_arbitrage_opportunity("American put option lower bound");
            cout << "buying a put option at " << put_option_ask;
            cout << " and immediately exercising it.\n";
            print_profit(((strike_price - asset_ask) - put_option_ask) - transaction_cost);
            cout << ((strike_price - asset_ask) - put_option_ask) - transaction_cost << " = ((";
            cout << strike_price << " - " << asset_ask << ") - " << put_option_ask << ")";
            print_transaction_cost(transaction_cost);
            check = true;
        }
    }
    return check;
}

bool check_option_lower_bound(int option_type, float asset_bid, float asset_ask, float call_option_ask, float put_option_ask, float strike_price)
{
    bool arbitrage_opportunity_1 = false;
    if (call_check)
        arbitrage_opportunity_1 = check_call_option_lower_bound(asset_bid, call_option_ask, strike_price);
    bool arbitrage_opportunity_2 = false;
    if (put_check)
        arbitrage_opportunity_2 = check_put_option_lower_bound(option_type, asset_ask, put_option_ask, strike_price);
    return arbitrage_opportunity_1 | arbitrage_opportunity_2;
}

bool check_convexity(int option_way, float option_bid_middle, float option_ask_low, float option_ask_high,
                     float strike_price_low, float strike_price_middle, float strike_price_high)
{
    float transaction_cost = 1.0 + 1.0 + 1.0;
    float w = (strike_price_high - strike_price_middle) / (strike_price_high - strike_price_low);
    if (option_bid_middle - (w * option_ask_low + (1 - w) * option_ask_high) > transaction_cost)
    {
        print_arbitrage_opportunity("convexity");
        string option;
        if (option_way == 1)
            option = "call";
        else if (option_way == 2)
            option = "put";
        cout << "buying " << w << " " << option << " option";
        cout << " with strike price " << strike_price_low;
        cout << " at " << option_ask_low;
        cout << " and " << 1 - w << " " << option << " option";
        cout << " with strike price " << strike_price_high;
        cout << " at " << option_ask_high;
        cout << " and a " << option << " option";
        cout << " with strike price " << strike_price_middle;
        cout << " at " << option_bid_middle;
        print_profit((option_bid_middle - (w * option_ask_low + (1 - w) * option_ask_high)) - transaction_cost);
        cout << (option_bid_middle - (w * option_ask_low + (1 - w) * option_ask_high)) - transaction_cost << " = (";
        cout << option_bid_middle << " - (" << w << " * " << option_ask_low << " + " << (1 - w) << " * " << option_ask_high << "))";
        print_transaction_cost(transaction_cost);
        return true;
    }
    return false;
}

bool check_convexity_order(int option_way, float option_bid_1, float option_bid_2, float option_bid_3,
                           float option_ask_1, float option_ask_2, float option_ask_3,
                           float strike_price_1, float strike_price_2, float strike_price_3)
{
    if (strike_price_1 < strike_price_2)
    {
        if (strike_price_3 > strike_price_2)
            return check_convexity(option_way, option_bid_2, option_ask_1, option_ask_3, strike_price_1, strike_price_2, strike_price_3);
        else if (strike_price_3 < strike_price_1)
            return check_convexity(option_way, option_bid_1, option_ask_3, option_ask_2, strike_price_3, strike_price_1, strike_price_2);
        else
            return check_convexity(option_way, option_bid_3, option_ask_1, option_ask_2, strike_price_1, strike_price_3, strike_price_2);
    }
    else
    {
        if (strike_price_3 < strike_price_2)
            return check_convexity(option_way, option_bid_2, option_ask_3, option_ask_1, strike_price_3, strike_price_2, strike_price_1);
        else if (strike_price_3 > strike_price_1)
            return check_convexity(option_way, option_bid_1, option_ask_2, option_ask_3, strike_price_2, strike_price_1, strike_price_3);
        else
            return check_convexity(option_way, option_bid_3, option_ask_2, option_ask_1, strike_price_2, strike_price_3, strike_price_1);
    }
}

bool check_future_and_option(float asset_bid, float asset_ask, float future_bid, float future_ask,
                             float call_option_bid, float call_option_ask, float put_option_bid, float put_option_ask, float strike_price)
{
    if (call_check && put_check == false)
        return false;
    float transaction_cost = 1.0 + 1.0 + 1.0;
    if ((put_option_bid + future_bid) - (call_option_ask + PV(strike_price)) > transaction_cost)
    {
        print_arbitrage_opportunity("futures with options");
        cout << "buying a call option at " << call_option_ask;
        // cout << " and a zero bond at present value of strike price " << strike_price << " at " << PV(strike_price);
        cout << ", saving at present value of strike price " << strike_price << " at " << PV(strike_price);
        cout << ", and selling a put option at " << put_option_bid;
        cout << " and a future at " << future_bid << ".\n";
        print_profit(((put_option_bid + future_bid) - (call_option_ask + PV(strike_price))) - transaction_cost);
        cout << ((put_option_bid + future_bid) - (call_option_ask + PV(strike_price))) - transaction_cost << " = ((";
        cout << put_option_bid << " + " << future_bid << ") - (" << call_option_ask << " + " << PV(strike_price) << "))";
        print_transaction_cost(transaction_cost);
        return true;
    }
    else if ((call_option_bid + PV(strike_price)) - (put_option_ask + future_ask) > transaction_cost)
    {
        print_arbitrage_opportunity("futures with options");
        cout << "buying a put option at " << put_option_ask;
        cout << " and an underlying asset at " << future_ask;
        cout << " and selling a call option at " << call_option_bid;
        // cout << " and a zero bond at present value of strike price " << strike_price << " at " << PV(strike_price) << ".\n";
        cout << ", and borrowing at present value of strike price " << strike_price << " at " << PV(strike_price) << ".\n";
        print_profit(((call_option_bid + PV(strike_price)) - (put_option_ask + future_ask)) - transaction_cost);
        cout << ((call_option_bid + PV(strike_price)) - (put_option_ask + future_ask)) - transaction_cost << " = ((";
        cout << call_option_bid << " + " << PV(strike_price) << ") - (" << put_option_ask << " + " << future_ask << "))";
        print_transaction_cost(transaction_cost);
        return true;
    }
    return false;
}

bool check_arbitrage_no_strike_price(float asset_bid, float asset_ask, float future_bid, float future_ask,
                                     float call_option_bid, float call_option_ask, float put_option_bid, float put_option_ask)
{
    bool arbitrage_opportunity_1 = check_bid_ask(asset_bid, asset_ask, future_bid, future_ask, call_option_bid, call_option_ask, put_option_bid, put_option_ask);
    bool arbitrage_opportunity_2 = check_future(asset_bid, asset_ask, future_bid, future_ask);
    if (!(arbitrage_opportunity_1 | arbitrage_opportunity_2))
        return false;
    return true;
}

bool check_arbitrage_one_strike_price(int option_type, float asset_bid, float asset_ask, float future_bid, float future_ask,
                                      float call_option_bid, float call_option_ask, float put_option_bid, float put_option_ask, float strike_price)
{
    bool arbitrage_opportunity_1 = false;
    if (option_type == 1)
        arbitrage_opportunity_1 = put_call_parity(asset_bid, asset_ask, call_option_bid, call_option_ask, put_option_bid, put_option_ask, strike_price);
    bool arbitrage_opportunity_2 = check_option_upper_bond(option_type, asset_ask, call_option_bid, put_option_bid, strike_price);
    bool arbitrage_opportunity_3 = check_option_lower_bound(option_type, asset_bid, asset_ask, call_option_ask, put_option_ask, strike_price);
    bool arbitrage_opportunity_4 = check_future_and_option(asset_bid, asset_ask, future_bid, future_ask, call_option_bid, call_option_ask, put_option_bid, put_option_ask, strike_price);
    if (!(arbitrage_opportunity_1 | arbitrage_opportunity_2 | arbitrage_opportunity_3 | arbitrage_opportunity_4))
    {
        cout << "There\'s no any arbitrage opportunity.\n";
        return false;
    }
    return true;
}
