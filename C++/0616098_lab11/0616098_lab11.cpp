#include <iostream>

using namespace std;

int main()
{
    int l,s;
    cin>>l>>s;
    int time=1;
    while(l&&s)                                             // l    s
    {
        int min=((1+l)*l)/2;                                // 26   351
        int max=((26-l+1)+26)*l/2;                          // 25   325~350
        int posible;                                        // 24   300~348
        if(s>max||s<min)                                    // 23   276~345
            posible=0;
        else                                                // 3    6~75
        {                                                   // 2    3~51
            if(l==1||l==25||l==26)                          // 1    1~26
                posible=1;
            else
            {
                int smh[27][27][351];                       //[numberofalphabat][length][sum]
                smh[0][0][0]=1;
                for(int alp=1;alp<=26;alp++)
                {
                    for(int num=0;num<=alp;num++)
                    {
                        for(int sum=0;sum<351;sum++)
                        {
                            smh[alp][num][sum]=smh[alp-1][num][sum];
                            if(num>0&&sum>=alp)
                                smh[alp][num][sum]+=smh[alp-1][num-1][sum-alp];
                        }
                    }
                }
                posible=smh[26][l][s];
            }
        }
        cout<<"Case "<<time++<<": "<<posible<<endl;
        cin>>l>>s;
    }
    return 0;
}
