#include <iostream>
#include "math.h"
using namespace std;

float interest_rate = 0.01844;
float year_duration = 1.0 / 12;

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
    float asset_bid = 0.0;
    float asset_ask = 0.0;
    cout << "Please input the bid price for underlying asset: ";
    cin >> asset_bid;
    cout << "Please input the ask price for underlying asset: ";
    cin >> asset_ask;
    float future_bid = 0.0;
    float future_ask = 0.0;
    cout << "Please input the bid price for future: ";
    cin >> future_bid;
    cout << "Please input the ask price for future: ";
    cin >> future_ask;
    float strike_price = 7757.0;
    cout << "Please input the strike price(X): ";
    cin >> strike_price;
    float call_option_bid = 0.0;
    float call_option_ask = 0.0;
    cout << "Please input the bid price for call option: ";
    cin >> call_option_bid;
    cout << "Please input the ask price for call option: ";
    cin >> call_option_ask;
    float put_option_bid = 0.0;
    float put_option_ask = 0.0;
    cout << "Please input the bid price for put option: ";
    cin >> put_option_bid;
    cout << "Please input the ask price for put option: ";
    cin >> put_option_ask;
    cout << "interest_rate = " << interest_rate << "\t" << "maturity = 1 month\n";
    // 1: European  2: American
    int option_type = 1;
    cout << "\n";
    check_arbitrage_no_strike_price(asset_bid, asset_ask, future_bid, future_ask,
                                    call_option_bid, call_option_ask, put_option_bid, put_option_ask);
    check_arbitrage_one_strike_price(option_type, asset_bid, asset_ask, future_bid, future_ask,
                                     call_option_bid, call_option_ask, put_option_bid, put_option_ask, strike_price);
    return 0;
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
        cout << call_option_bid_high << " - " << call_option_ask_low << ")";
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
        cout << option_bid_middle << " - (" << w << " * " << option_ask_low << " + " << (1 - w) << " * " << option_ask_high << "))";
        print_transaction_cost(transaction_cost);
        return true;
    }
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
    {
        cout << "there\'s no any arbitrage opportunity.\n";
        return false;
    }
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
