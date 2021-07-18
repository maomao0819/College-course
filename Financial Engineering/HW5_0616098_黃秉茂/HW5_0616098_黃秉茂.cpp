#include <iostream>
#include "math.h"
using namespace std;

#define face_value 100
#define tolerance 0.000001

int main()
{
    int n_term = 0;
    cout << "Please input the number of the terms (n): ";
    cin >> n_term;
    float ZeroRate[n_term] = {0};
    float Yield[n_term]= {0};
    float coupon = 0;
    cout << "Please input the coupon (C): ";
    cin >> coupon;
    for (int term_idx = 0; term_idx < n_term; term_idx++)
    {
        cout << "Please input " << term_idx + 1 << "th term Yield (R): ";
        cin >> Yield[term_idx];
    }
    float yield_spread = 0;
    cout << "Please input the yield spread (S): ";
    cin >> yield_spread;
    ZeroRate[0] = Yield[0];
    // calculate zero rate with bootstrapping method
    for (int total_term_idx = 1; total_term_idx <= n_term - 1; total_term_idx++)
    {
        float BondValue = 0;
        for (int term_idx = 0; term_idx <= total_term_idx; term_idx++)
        {
            float Discount = 1;
            for (int discount_term_idx = 0; discount_term_idx <= term_idx; discount_term_idx++)
                Discount /= (1 + Yield[total_term_idx]);
            BondValue += Discount * coupon;
            if (term_idx == total_term_idx)
                BondValue += Discount * face_value;
        }
        for (int term_idx = 0; term_idx < total_term_idx; term_idx++)
        {
            float PV = coupon;
            for (int i = 0; i <= term_idx; i++)
                PV /= (1 + ZeroRate[term_idx]);
            BondValue -= PV;
        }
        ZeroRate[total_term_idx] = pow((coupon + face_value) / BondValue, 1.0 / (total_term_idx + 1)) - 1;
    }
    // for (int term_idx = 0; term_idx < n_term; term_idx++)
    //     cout << term_idx + 1 << "th term zero rate is " << ZeroRate[term_idx] << endl;

    // calculate static spread with bisection method
    float BondValue_BondYield = 0;
    for (int term_idx = 0; term_idx <= n_term - 1; term_idx++)
    {
        float Discount = 1;
        for (int discount_term_idx = 0; discount_term_idx <= term_idx; discount_term_idx++)
            Discount /= (1 + yield_spread + Yield[n_term - 1]);
        BondValue_BondYield += Discount * coupon;
        if (term_idx == n_term - 1)
            BondValue_BondYield += Discount * face_value;
    }
    float Low = 0, High = 1;
    while (High - Low >= tolerance)
    {
        float Middle = (Low + High) / 2;
        float BondValue_ZeroRate = 0;
        for (int term_idx = 0; term_idx <= n_term - 1; term_idx++)
        {
            float Discount = 1;
            for (int discount_term_idx = 0; discount_term_idx <= term_idx; discount_term_idx++)
                Discount /= (1 + Middle + ZeroRate[discount_term_idx]);
            BondValue_ZeroRate += Discount * coupon;
            if (term_idx == n_term - 1)
                BondValue_ZeroRate += Discount * face_value;
        }
        if (BondValue_ZeroRate < BondValue_BondYield)
            High = Middle;
        else
            Low = Middle;
    }
    cout << "static spread = " << (Low + High) / 2;
    return 0;
}
