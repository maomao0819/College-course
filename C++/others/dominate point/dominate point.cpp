#include <iostream>

using namespace std;

int main()
{
    cout<<"Please input n:";
    int n;
    cin>>n;
    while(n<1||n>32767)
    {
        cout<<"Wrong input!\nPlease input another integer(1~32767):";
        cin>>n;
    }
    cout<<"Please input "<<n;
    if(n==1)
    {
        cout<<" point:\n";
        int point_x,point_y;
        cin>>point_x>>point_y;
        cout<<"The rank of point ("<<point_x<<","<<point_y<<"): 0";
    }
    else
    {
        cout<<" points:\n";
        int point[n][2];
        for(int i=0;i<n;i++)
        {
            cin>>point[i][0];
            while(point[i][0]<-32767||point[i][0]>32767)
            {
                cout<<"Wrong input!\nPlease input another integer(-32767~32767):\n";
                cin>>point[i][0];
            }
            cin>>point[i][1];
            while(point[i][1]<-32767||point[i][1]>32767)
            {
                cout<<"Wrong input!\nPlease input another integer(-32767~32767):\n"<<point[i][0]<<" ";
                cin>>point[i][1];
            }
        }

        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n-i-1;j++)
            {
                if((point[j][0]+point[j][1])<(point[j+1][0]+point[j+1][1]))
                {
                    int temp[2]={point[j][0],point[j][1]};
                    point[j][0]=point[j+1][0];
                    point[j][1]=point[j+1][1];
                    point[j+1][0]=temp[0];
                    point[j+1][1]=temp[1];
                }
            }
        }
        int sum[n]={0};
        for(int i=0;i<n-1;i++)
        {
            for(int j=i+1;j<n;j++)
            {
                if((point[i][0]>point[j][0])&&(point[i][1]>point[j][1]))
                    sum[i]++;
            }
        }
        for(int i=0;i<n;i++)
            cout<<"The rank of point ("<<point[i][0]<<","<<point[i][1]<<"): "<<sum[i]<<"\n";
    }
    return 0;
}
