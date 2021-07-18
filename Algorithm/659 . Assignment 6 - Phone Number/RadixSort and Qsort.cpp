#include <iostream>
#include <iomanip>
using namespace std;
void quicksort(int a[][2], int le, int ri);
int partition(int a[][2], int le, int ri);
void RadixSort(int arr[][2],int n);
void CountSort(int arr[][2],int n,int exp,int output[]);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    short time;
    cin>>time;
    while(time--)
    {
        unsigned short num;
        cin>>num;
        string str;
        int inta[num+1][2]={0};
        inta[num][0]=99999999;
        for(unsigned short i=0;i<num;i++)
        {
            cin>>str;
            int digit=1000000;
            for(int j=0;j<str.length()&&digit;j++)
            {
                switch(str[j])
                {
                    case '0':
                        digit/=10;
                        break;
                    case '1':
                        inta[i][0]+=digit;
                        digit/=10;
                        break;
                    case 'A': case 'B': case 'C': case '2':
                        inta[i][0]+=2*digit;
                        digit/=10;
                        break;
                    case 'D': case 'E': case 'F': case '3':
                        inta[i][0]+=3*digit;
                        digit/=10;
                        break;
                    case 'G': case 'H': case 'I': case '4':
                        inta[i][0]+=4*digit;
                        digit/=10;
                        break;
                    case 'J': case 'K': case 'L': case '5':
                        inta[i][0]+=5*digit;
                        digit/=10;
                        break;
                    case 'M': case 'N': case 'O': case '6':
                        inta[i][0]+=6*digit;
                        digit/=10;
                        break;
                    case 'P': case 'R': case 'S': case '7':
                        inta[i][0]+=7*digit;
                        digit/=10;
                        break;
                    case 'T': case 'U': case 'V': case '8':
                        inta[i][0]+=8*digit;
                        digit/=10;
                        break;
                    case 'W': case 'X': case 'Y': case '9':
                        inta[i][0]+=9*digit;
                        digit/=10;
                }
            }
        }
        if(num<150)
            quicksort(inta, 0, num-1);
        else
            RadixSort(inta, num);
        int mark=0;
        for(unsigned short i=0;i<num;i++)
        {
            if(inta[i][0]==inta[i+1][0])
            {
                inta[i+1][1]+=1+inta[i][1];
                if(!mark)
                    mark++;
            }
            else if(inta[i][1])
                cout<<setw(3)<<setfill('0')<<inta[i][0]/10000<<"-"<<setw(4)<<setfill('0')<<inta[i][0]%10000<<" "<<inta[i][1]+1<<"\n";
        }
        if(mark)
            cout<<"\n";
        else
            cout<<"No duplicate."<<"\n"<<"\n";
    }
    return 0;
}
void quicksort(int a[][2], int le, int ri)
{
    if(le<ri)
    {
        int p=partition(a, le, ri);
        quicksort(a, le, p-1);
        quicksort(a, p+1, ri);
    }
}
int partition(int a[][2], int le, int ri)
{
    int pivot=a[ri][0];
    int p=le-1;
    int temp;
    for(int i=le;i<ri;i++)
    {
        if(a[i][0]<=pivot)
        {
            p++;
            temp=a[i][0];
            a[i][0]=a[p][0];
            a[p][0]=temp;
        }
    }
    temp=a[p+1][0];
    a[p+1][0]=a[ri][0];
    a[ri][0]=temp;
    return p+1;
}
void CountSort(int arr[][2],int n,int exp,int output[])
{
    int i,count[10]={0};
    for(i=0;i<n;i++)
        count[(arr[i][0]/exp)%10]++;
    for(i=1;i<10;i++)
        count[i]+=count[i-1];
    for(i=n-1;i>=0;i--)
    {
        output[count[(arr[i][0]/exp)%10]-1]=arr[i][0];
        count[(arr[i][0]/exp)%10]--;
    }
    for(i=0;i<n;i++)
        arr[i][0]=output[i];
}
void RadixSort(int arr[][2],int n)
{
    int output[n];
    for(int exp=1;exp<=1000000;exp*= 10)
        CountSort(arr,n,exp,output);
}
