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

float interest_rate = 0.01844;
float year_duration = 1.0 / 12;

vector <pair <string, vector <pair <string, vector<string> > > > > read_csv(string filename);

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
    // declaration and initialization
    vector <pair <string, vector <pair <string, vector<string> > > > > file = read_csv("TAIEX.csv");
    // file.at(option_type).second.at(column).second.at(data_idx);
    int n_data = file.at(1).second.at(1).second.size();

    // 1: European  2: American
    int option_type = 1;
    float asset_bid = 7757.0;
    float asset_ask = 7758.0;
    float future_bid = 7756.0;
    float future_ask = 7760.0;
    float strike_price [n_data] = {};
    float call_option_bid [n_data] = {};
    float call_option_ask [n_data] = {};
    float put_option_bid [n_data] = {};
    float put_option_ask [n_data] = {};

    string dot_line(50, '-');
    cout << "<<<" << dot_line << "   TAIEX   " << dot_line << ">>>\n";
    cout << "INTEREST RATE = " << interest_rate << "\t\t" << "MATURITY = 1 MONTH\n";
    cout << "TAIEX's BID = " << asset_bid << "\t\t" << "TAIEX's ASK =" << asset_ask << "\t\t";
    cout << "FUTURE's BID = " << future_bid << "\t\t" << "FUTURE's ASK =" << future_ask << "\n";
    cout << file.at(0).first << "\t\t\t\t\t\t\t" << file.at(1).first << "\n";
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < n_data / 2 - 1; j++)
            cout << file.at(i).second.at(j).first << "\t";
        cout << "\t";
    }

    cout << endl;
    for (int data_idx = 0; data_idx < n_data; data_idx++)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < n_data / 2 - 1; j++)
                cout << file.at(i).second.at(j).second.at(data_idx) << "\t";
            cout << "\t";
        }
        cout << endl;
    }

    for (int data_idx = 0; data_idx < n_data; data_idx++)
    {
        strike_price[data_idx] = atof(file.at(0).second.at(0).second.at(data_idx).c_str());
        call_option_bid[data_idx] = atof(file.at(0).second.at(3).second.at(data_idx).c_str());
        call_option_ask[data_idx] = atof(file.at(0).second.at(4).second.at(data_idx).c_str());
        put_option_bid[data_idx] = atof(file.at(1).second.at(3).second.at(data_idx).c_str());
        put_option_ask[data_idx] = atof(file.at(1).second.at(4).second.at(data_idx).c_str());
    }

    string dot_line2(10, '-');
    cout << "\n\n<" << dot_line2 << "   WHEN NO CONSIDER STRIKE PRICE.   " << dot_line2 << ">\n";
    bool arbitrage_no_strike = false;
    for (int data_idx = 0; data_idx < n_data; data_idx++)
    {
        bool cond1 = (call_option_bid[data_idx] || call_option_ask[data_idx]);
        bool cond2 = (put_option_bid[data_idx] || put_option_ask[data_idx]);
        if (cond1 && cond2)
        {
            bool check = check_arbitrage_no_strike_price(asset_bid, asset_ask, future_bid, future_ask,
                                                         call_option_bid[data_idx], call_option_ask[data_idx],
                                                         put_option_bid[data_idx], put_option_ask[data_idx]);
            if (check)
                arbitrage_no_strike = true;
        }
        else
        {
            if (cond1 == false)
                cout << "Some of the call option data is missing when the strike price is " << strike_price[data_idx] << ".\n";
            if (cond2 == false)
                cout << "Some of the put option data is missing the strike price is " << strike_price[data_idx] << ".\n";
        }
    }
    if (arbitrage_no_strike == false)
        cout << "There\'s no any arbitrage opportunity on bid and ask price.";
    cout << "\n\n\n\n";

    cout << dot_line2 << "   WHEN ONLY CONSIDER ONE STRIKE PRICE.   " << dot_line2 << ">\n";
    for (int data_idx = 0; data_idx < n_data; data_idx++)
    {
        cout << "When the strike price is " << strike_price[data_idx] << ".\n";
        bool cond1 = (call_option_bid[data_idx] || call_option_ask[data_idx]);
        bool cond2 = (put_option_bid[data_idx] || put_option_ask[data_idx]);
        if (cond1 && cond2)
            check_arbitrage_one_strike_price(option_type, asset_bid, asset_ask, future_bid, future_ask,
                                             call_option_bid[data_idx], call_option_ask[data_idx],
                                             put_option_bid[data_idx], put_option_ask[data_idx],
                                             strike_price[data_idx]);
        else
        {
            if (cond1 == false)
                cout << "Some of the call option data is missing.\n";
            if (cond2 == false)
                cout << "Some of the put option data is missing.\n";
        }
        cout << "\n\n";
    }

    cout << "\n<" << dot_line2 << "   WHEN CONSIDER 2 STRIKE PRICEs.   " << dot_line2 << ">\n";
    bool arbitrage_two_strike = false;
    for (int data_idx_1 = 0; data_idx_1 < n_data; data_idx_1++)
    {
        for (int data_idx_2 = data_idx_1 + 1; data_idx_2 < n_data; data_idx_2++)
        {
            bool cond1 = (call_option_bid[data_idx_1] || call_option_ask[data_idx_1]);
            bool cond2 = (put_option_bid[data_idx_1] || put_option_ask[data_idx_1]);
            bool cond3 = (call_option_bid[data_idx_2] || call_option_ask[data_idx_2]);
            bool cond4 = (put_option_bid[data_idx_2] || put_option_ask[data_idx_2]);
            if ((cond1 && cond2 && cond3 && cond4) == false)
                continue;
            else
            {
                bool check = check_option_with_strike_price(call_option_bid[data_idx_1], call_option_bid[data_idx_2], call_option_ask[data_idx_1], call_option_ask[data_idx_2],
                                                       put_option_bid[data_idx_1], put_option_bid[data_idx_2], put_option_ask[data_idx_1], put_option_ask[data_idx_2],
                                                       strike_price[data_idx_1] , strike_price[data_idx_2]);
                if (check)
                    arbitrage_two_strike = true;
            }
        }
    }
    if (arbitrage_two_strike == false)
        cout << "There\'s no any arbitrage opportunity.\n";
    cout << "\n\n\n";

    cout << "<" << dot_line2 << "   WHEN CONSIDER 3 STRIKE PRICEs.   " << dot_line2 << ">\n";
    bool arbitrage_three_strike = false;
    for (int data_idx_1 = 0; data_idx_1 < n_data; data_idx_1++)
    {
        for (int data_idx_2 = data_idx_1 + 1; data_idx_2 < n_data; data_idx_2++)
        {
            for (int data_idx_3 = data_idx_2 + 1; data_idx_3 < n_data; data_idx_3++)
            {
                bool cond1 = (call_option_bid[data_idx_1] || call_option_ask[data_idx_1]);
                bool cond2 = (put_option_bid[data_idx_1] || put_option_ask[data_idx_1]);
                bool cond3 = (call_option_bid[data_idx_2] || call_option_ask[data_idx_2]);
                bool cond4 = (put_option_bid[data_idx_2] || put_option_ask[data_idx_2]);
                bool cond5 = (call_option_bid[data_idx_3] || call_option_ask[data_idx_3]);
                bool cond6 = (put_option_bid[data_idx_3] || put_option_ask[data_idx_3]);

                bool check1 = false;
                if (cond1 && cond3 && cond5)
                    check1 = check_convexity_order(1, call_option_bid[data_idx_1], call_option_bid[data_idx_2], call_option_bid[data_idx_3],
                                                   call_option_ask[data_idx_1], call_option_ask[data_idx_2], call_option_ask[data_idx_3],
                                                   strike_price[data_idx_1] , strike_price[data_idx_2], strike_price[data_idx_3]);
                bool check2 = false;
                if (cond2 && cond4 && cond6)
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
    if (asset_bid - asset_ask > transaction_cost)
    {
        print_arbitrage_opportunity("Bid-Ask");
        cout << "You have an arbitrage opportunity with buying an underlying asset at " << asset_ask;
        cout << " and selling an underlying asset at " << asset_bid << ".\n";
        print_profit((asset_bid - asset_ask) - transaction_cost);
        cout << (asset_bid - asset_ask) - transaction_cost << " = (" << asset_bid << " - " << asset_ask << ")";
        print_transaction_cost(transaction_cost);
        check = true;
    }
    if (future_bid - future_bid > transaction_cost)
    {
        print_arbitrage_opportunity("Bid-Ask");
        cout << "buying a future at " << future_ask;
        cout << " and selling a future at " << future_bid << ".\n";
        print_profit((future_bid - future_ask) - transaction_cost);
        cout << (future_bid - future_ask) - transaction_cost << " = (" << future_bid << " - " << future_ask << ")";
        print_transaction_cost(transaction_cost);
        check = true;
    }
    if (call_option_bid - call_option_bid > transaction_cost)
    {
        print_arbitrage_opportunity("Bid-Ask");
        cout << "buying a call option at " << call_option_ask;
        cout << " and selling a call option at " << call_option_bid << ".\n";
        print_profit((call_option_bid - call_option_ask) - transaction_cost);
        cout << (call_option_bid - call_option_ask) - transaction_cost << " = (" << call_option_bid << " - " << call_option_ask << ")";
        print_transaction_cost(transaction_cost);
        check = true;
    }
    if (put_option_bid - put_option_bid > transaction_cost)
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
        return true;
    }
    return false;
}

bool put_call_parity(float asset_bid, float asset_ask, float call_option_bid, float call_option_ask, float put_option_bid, float put_option_ask, float strike_price)
{
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
    if (call_option_bid_high - call_option_ask_low > transaction_cost)
    {
        print_arbitrage_opportunity("call option with different strike prices");
        cout << "buying a call option with strike price " << strike_price_low;
        cout << " at " << call_option_ask_low;
        cout << " and selling a call option with strike price " << strike_price_high;
        cout << " at " << call_option_bid_high << ".\n";
        print_profit((call_option_bid_high - call_option_ask_low) - transaction_cost);
        cout << (call_option_bid_high - call_option_ask_low) - transaction_cost << " = (";
        cout << call_option_bid_high << " - " << call_option_ask_low << ")\n";
        print_transaction_cost(transaction_cost);
        check = true;
    }
    if (put_option_bid_low - put_option_ask_high > transaction_cost)
    {
        print_arbitrage_opportunity("call option with different strike prices");
        cout << "buying a put option with strike price " << strike_price_high;
        cout << " at " << put_option_ask_high;
        cout << " and selling a put option with strike price " << strike_price_low;
        cout << " at " << put_option_bid_low << ".\n";
        print_profit((put_option_bid_low - put_option_ask_high) - transaction_cost);
        cout << (put_option_bid_low - put_option_ask_high) - transaction_cost << " = (";
        cout << put_option_bid_low << " - " << put_option_ask_high << ")\n";
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
    bool arbitrage_opportunity_1 = check_call_option_upper_bound(asset_ask, call_option_bid);
    bool arbitrage_opportunity_2 = check_put_option_upper_bound(option_type, put_option_bid, strike_price);
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
    bool arbitrage_opportunity_1 = check_call_option_lower_bound(asset_bid, call_option_ask, strike_price);
    bool arbitrage_opportunity_2 = check_put_option_lower_bound(option_type, asset_ask, put_option_ask, strike_price);
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
        cout << option_bid_middle << " - (" << w << " * " << option_ask_low << " + " << (1 - w) << " * " << option_ask_high << "))\n";
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
        cout << "there\'s no any arbitrage opportunity.\n";
        return false;
    }
    return true;
}
