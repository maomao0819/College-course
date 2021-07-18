#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
struct turtle {
    int w, s;
};
bool cmp(turtle a, turtle b) {
    return a.s < b.s;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int size;
    cin>>size;
    turtle A[size];
    int n = 0, i, j;
    for(n=0;n<size;n++)
        cin>>A[n].w>>A[n].s;

    sort(A, A+n, cmp);
    int dp[size];
    for(i = 0; i <= n; i++)
        dp[i] = 0xfffffff;
    dp[0] = 0;
    for(i = 0; i < n; i++) {
        for(j = n; j >= 1; j--) {
            if(dp[j-1]+A[i].w <= A[i].s) {
                dp[j] = min(dp[j], dp[j-1]+A[i].w);
            }
        }
    }
    for(i = n; i >= 0; i--) {
        if(dp[i] != 0xfffffff)
            break;
    }
    cout<<i<<endl;
    for(i = n; i >= 0; i--)
        cout<<dp[i]<<endl;
    return 0;
}
