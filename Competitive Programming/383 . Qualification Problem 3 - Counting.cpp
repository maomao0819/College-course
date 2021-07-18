#include <iostream>
#include <string>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    int num_0 = 0;
    int num_1 = 0;
    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] == '1')
            num_1++;
        else
            num_0++;
    }
    cout << num_0 << " " << num_1;
    return 0;
}
