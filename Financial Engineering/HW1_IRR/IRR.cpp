#include <iostream>
#include <stdio.h>
using namespace std;

#define tolerance 0.0001
double calaulate_PV(double r, double initial_invest, int n_term, double cash_flow[]);
double calaulate_derivative_PV(double r, int n_term, double cash_flow[]);
int main()
{
    //-----------bisection----------------
    cout << "By bisection:" << endl;
    double discount_rate;
    int n_term = 2;
    double initial_invest = 9702;
    double cash_flow[n_term] = {-19700, 10000};
    double Low = 0, High = 1;
    // y = 9702 * (1 + r) ^ 2 - 19700 * (1 + r) + 10000
    // y = 9702 * r ^ 2 - 296 * r + 2
    double a = 9702, b = -296, c = 2;
    // 拋物線頂點
    double Vertex = -b / (2 * a);
    //右方拋物線斜率為正
    while (High - Vertex >= tolerance)
    {
        double Middle = (Vertex + High) / 2;
        double PV = calaulate_PV(Middle, initial_invest, n_term, cash_flow);
        if (PV > 0)
            High = Middle;
        else
            Vertex = Middle;
    }
    cout << "Yield rate = " << High << "\n";
    //左方拋物線斜率為負
    while (Vertex - Low >= tolerance)
    {
        double Middle = (Low + Vertex) / 2;
        double PV = calaulate_PV(Middle, initial_invest, n_term, cash_flow);
        if (PV > 0)
            Low = Middle;
        else
            Vertex = Middle;
    }
    cout << "Yield rate = " << Vertex;
    cout << endl << endl;

    //-----------Newton method----------------
    cout << "By Newton method:" << endl;
    //右根
    double root = 1;
    double PV = calaulate_PV(root, initial_invest, n_term, cash_flow);
    double derivative_PV = 0;
    while (PV >= tolerance)
    {
        PV = calaulate_PV(root, initial_invest, n_term, cash_flow);
        discount_rate = 1 / (1 + root);
        derivative_PV = 0;
        for (int i = 0; i < n_term; i++)
        {
            discount_rate /= (1 + root);
            derivative_PV -= (i + 1) * discount_rate * cash_flow[i];
        }
        root -= (PV / derivative_PV);
    }
    cout << "Yield rate = " << root <<"\n";
    //左根
    root = 0;
    PV = calaulate_PV(root, initial_invest, n_term, cash_flow);
    while (PV >= tolerance)
    {
        PV = calaulate_PV(root, initial_invest, n_term, cash_flow);
        derivative_PV = calaulate_derivative_PV(root, n_term, cash_flow);
        root -= (PV / derivative_PV);
    }
    cout << "Yield rate = " << root <<"\n";
    return 0;
}

double calaulate_PV(double r, double initial_invest, int n_term, double cash_flow[])
{
    double PV = 0;
    double discount_rate = 1;
    for (int i = 0; i < n_term; i++)
    {
        discount_rate /= (1 + r);
        PV += discount_rate * cash_flow[i];
    }
    PV += initial_invest;
    return PV;
}

double calaulate_derivative_PV(double r, int n_term, double cash_flow[])
{
    double discount_rate = 1 / (1 + r);
    double derivative_PV = 0;
    for (int i = 0; i < n_term; i++)
    {
        discount_rate /= (1 + r);
        derivative_PV -= (i + 1) * discount_rate * cash_flow[i];
    }
    return derivative_PV;
}
