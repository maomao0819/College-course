#include <iostream>

using namespace std;

int main()
{
    int length,time;
    cin>>length>>time;
    int multiof2=1;
    while(multiof2<length)
        multiof2*=2;
    //a[i][0]:index a[i][1]:value
    int a[2*multiof2-1][2]={0};
    for(int i=0;i<2*multiof2-1;i++)
        a[i][0]=i;
    for(int i=multiof2-1;i<multiof2-1+length;i++)
        cin>>a[i][1];
    for(int i=multiof2-2;i>=0;i--)
    {
        a[i][1]=(a[2*i+1][1]<a[2*i+2][1])?a[2*i+2][1]:a[2*i+1][1];
        a[i][0]=(a[2*i+1][1]<a[2*i+2][1])?a[2*i+2][0]:a[2*i+1][0];
        while(a[i][0]<multiof2-1)
            a[i][0]=a[a[i][0]][0];
    }
    for(int i=0;i<2*multiof2-1;i++)
        cout<<"a["<<i<<"][0]="<<a[i][0]<<endl;
    for(int i=0;i<2*multiof2-1;i++)
        cout<<"a["<<i<<"][1]="<<a[i][1]<<endl;

    while(time--)
    {
        int r,l;
        cin>>r>>l;
        r+=(multiof2-2);
        l+=(multiof2-2);
        int max=r;
        /*for(int i=r;i<l;i++)
            if(a[i]<a[i+1])
                max=i;*/
        cout<<max<<endl;
    }
    return 0;
}
