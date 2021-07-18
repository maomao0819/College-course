#include <iostream>
#include <math.h>
using namespace std;
#define PERCENT 0.01
int main()
{
    int N_year = 7;
    float swap_rate[N_year];
    float spot_rate_discrete[N_year];
    float spot_rate_continuous[N_year];
    for (int i = 0; i < N_year; i++)
    {
        swap_rate[i] = 0;
        spot_rate_discrete[i] = 0;
        spot_rate_continuous[i] = 0;
    }
    swap_rate[0] = 2.26 * PERCENT;
    swap_rate[1] = 2.275 * PERCENT;
    swap_rate[2] = 2.285 * PERCENT;
    swap_rate[4] = 2.355 * PERCENT;
    swap_rate[3] = (swap_rate[2] + swap_rate[4]) / 2;
    swap_rate[6] = 2.44 * PERCENT;
    swap_rate[5] = (swap_rate[4] + swap_rate[6]) / 2;
    for (int i = 0; i < N_year; i++)
    {
        // discrete
        float value1 = 0;
        for (int j = 0; j < i; j++)
            value1 += swap_rate[i] / pow(1 + spot_rate_discrete[j], j + 1);
        spot_rate_discrete[i] = pow((1 + swap_rate[i]) / (1 - value1), 1.0 / (i + 1)) - 1;
        cout << i + 1 << "th discrete spot rate is " << spot_rate_discrete[i] / PERCENT << "%." << endl;

        // continuous
        float value2 = 0;
        for (int j = 0; j < i; j++)
            value2 += exp(-spot_rate_continuous[j] * (j + 1));
        spot_rate_continuous[i] = -log((1.0 - swap_rate[i] * value2) / (1.0 + swap_rate[i])) / (i + 1);
        cout << i + 1 << "th continuous spot rate is " << spot_rate_continuous[i] / PERCENT << "%." << endl;
    }
    return 0;
}
