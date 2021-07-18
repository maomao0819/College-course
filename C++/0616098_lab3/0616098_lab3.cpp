#include <iostream>
using namespace std;
int main()
{
    int time=1;
    while(20)
    {
        int row,col;
        cin>>row>>col;
        if(row==0&&col==0)
            break;
        int i,j,k,l;
        char cop[row+2][col+2];
        for(i=0;i<row+2;i++)
        {
            for(j=0;j<col+2;j++)
            {
                cop[i][j]='.';
            }
        }
        for(i=1;i<row+1;i++)
        {
            for(j=1;j<col+1;j++)
            {
                cin>>cop[i][j];
            }
        }
        char coun[row+2][col+2];
        for(i=0;i<row+2;i++)
        {
            for(j=0;j<col+2;j++)
            {
                coun[i][j]='0';
            }
        }
        // correct
        for(i=1;i<row+1;i++)
        {
            for(j=1;j<col+1;j++)
            {
                for(k=i-1;k<=i+1;k++)
                {
                    for(l=j-1;l<=j+1;l++)
                    {
                        if(cop[k][l]=='*')
                            coun[i][j]+=1;
                    }
                }
            }
        }
        for(i=0;i<row;i++)
        {
            for(j=0;j<col;j++)
            {
                if(cop[i+1][j+1]=='*')
                    coun[i+1][j+1]='*';
            }
        }
        if(time!=1&&row!=0&&col!=0)
            cout<<endl;
        cout<<"Field #"<<time++<<":"<<endl;
        for(i=1;i<row+1;i++)
        {
            for(j=1;j<col+1;j++)
            {
                cout<<coun[i][j];
            }
            cout<<endl;
        }
    }
    return 0;
}
