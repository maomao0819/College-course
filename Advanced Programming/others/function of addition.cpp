#include <iostream>
using namespace std;
int Add(int x);
void Add2(int &x);
void Add3(int *x);
void Add4(int x);
void Add5(int &x);
int main()
{
    int x = 10;
    cout << x << endl;
    x = Add(x);
    cout << x << endl;
    Add2(x);
    cout << x << endl;
    Add3(&x);
    cout << x << endl;
    Add4(x);
    cout << x << endl;
}
int Add(int x)
{
    return x + 10;
}
void Add2(int &x)
{
    x += 10;
    return;
}
void Add3(int *x)
{
    *x += 10;
    return;
}
void Add4(int x)
{
    int *p;
    p = &x;
    *p += 10;
    return;
}
