#include <iostream>

using namespace std;

int main()
{
    int time;
    cin>>time;
    int arrof2[31]={0};
    arrof2[0]=1;
    for(int i=1;i<31;i++)
        arrof2[i]=2*arrof2[i-1];
    long long int matrix[2][2][31]={0};
    matrix[0][0][0]=1;
    matrix[0][1][0]=2;
    matrix[1][0][0]=1;
    matrix[1][1][0]=0;
    int prime=999999937;
    for(int k=0;k<30;k++)
    {
        for(int i=0;i<2;i++)
        {
            for(int j=0;j<2;j++)
            {
                if(matrix[i][j][k]>prime)
                    matrix[i][j][k]%=prime;
            }
        }
        matrix[0][0][k+1]=(((matrix[0][0][k]*matrix[0][0][k])%prime)+((matrix[0][1][k]*matrix[1][0][k])%prime))%prime;
        matrix[0][1][k+1]=(((matrix[0][0][k]*matrix[0][1][k])%prime)+((matrix[0][1][k]*matrix[1][1][k])%prime))%prime;
        matrix[1][0][k+1]=(((matrix[1][0][k]*matrix[0][0][k])%prime)+((matrix[1][1][k]*matrix[1][0][k])%prime))%prime;
        matrix[1][1][k+1]=(((matrix[1][0][k]*matrix[0][1][k])%prime)+((matrix[1][1][k]*matrix[1][1][k])%prime))%prime;
    }
    while(time--)
    {
        int num;
        cin>>num;
        int check=1;
        if(num==1||num==2)
        {
            cout<<"1";
            check=0;
        }
        int deg=0;
        int matrix1[2][2]={1,0,0,1};
        int a1=1;
        int a2=1;
        int tempnum=num;
        while(tempnum/=2)
            deg++;
        if(check)
        {
            num-=2;
            while(num>0)
            {
                if(num>=arrof2[deg])
                {
                    int temp[4]={matrix1[0][0],matrix1[0][1],matrix1[1][0],matrix1[1][1]};
                    matrix1[0][0]=(((temp[0]*matrix[0][0][deg])%prime)+((temp[1]*matrix[1][0][deg])%prime))%prime;
                    matrix1[0][1]=(((temp[0]*matrix[0][1][deg])%prime)+((temp[1]*matrix[1][1][deg])%prime))%prime;
                    matrix1[1][0]=(((temp[2]*matrix[0][0][deg])%prime)+((temp[3]*matrix[1][0][deg])%prime))%prime;
                    matrix1[1][1]=(((temp[2]*matrix[0][1][deg])%prime)+((temp[3]*matrix[1][1][deg])%prime))%prime;
                    num-=arrof2[deg];
                }
                deg--;
            }
            cout<<(matrix1[0][0]+matrix1[0][1])%prime;
        }
        cout<<endl;
    }
    return 0;
}

