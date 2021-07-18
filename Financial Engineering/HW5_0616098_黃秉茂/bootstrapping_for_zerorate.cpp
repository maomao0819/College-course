#include <iostream>
#include "math.h"
using namespace std;
#define face_value 100

int main()
{
    int n_term = 0;
    cout << "Please input the number of the terms: ";
    cin >> n_term;
    float ZeroRate[n_term] = {0};
    float Yield[n_term]= {0};
    float coupon = 0;
    cout << "Please input the coupon: ";
    cin >> coupon;
    for (int term_idx = 0; term_idx < n_term; term_idx++)
    {
        cout << "Please input " << term_idx + 1 << "th term Yield: ";
        cin >> Yield[term_idx];
    }
    ZeroRate[0] = Yield[0];
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
    for (int term_idx = 0; term_idx < n_term; term_idx++)
        cout << term_idx + 1 << "th term zero rate is " << ZeroRate[term_idx] << endl;
    return 0;
}

