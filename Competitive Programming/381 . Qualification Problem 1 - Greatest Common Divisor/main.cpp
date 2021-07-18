#include <iostream>

using namespace std;
int gcd(int a, int b);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int a, b;
    cin >> a >> b;
    if(a > b)
    {
        int c = a;
        a = b;
        b = c;
    }
    int GCD = gcd(a, b);
    if(GCD < 0)
        GCD *= -1;
    cout << GCD << endl;
    return 0;
}
int gcd(int a, int b)
{
    b = b % a;
    if(!b)
        return a;
    return gcd(b, a);
}
