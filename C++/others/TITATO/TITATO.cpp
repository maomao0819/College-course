#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
void print(char t[]);
int checkwin(int index[],int n);
void print_line(int index1,int index2,int index3);
int main()
{
    int check=1;
    while(check)
    {
        cout<<"Welcome to TITATO game"<<endl;
        char t[9]={'1','2','3','4','5','6','7','8','9'};
        print(t);
        cout<<"Who first?(1 for you and 2 for me): ";
        int order;
        cin>>order;
        cout<<"'O' for you and 'X' for me"<<endl;
        int index_o[5];
        int index_x[5];
        int index_total[9];
        int no=0,nx=0,nt=0;
        int index;
        int checkr;
        int checki;
        srand(time(NULL));
        if(order==1)
        {
            while(1)
            {
                cout<<"Please input next position you select: ";
                checki=1;
                while(checki)
                {
                    cin>>index;
                    checki=0;
                    for(int i=0;i<nt;i++)
                    {
                        if(index==index_total[i])
                        {
                            cout<<index<<" is already here, please input another number: ";
                            checki=1;
                        }
                    }
                }
                t[index-1]='O';
                index_o[no++]=index;
                index_total[nt++]=index;
                print(t);
                if(no>=3)
                    if(checkwin(index_o,no)==1)
                    {
                        cout<<"You win."<<endl;
                        break;
                    }
                if(nt==9)
                {
                    cout<<"tie"<<endl;
                    break;
                }
                int r=rand()%8+1;
                checkr=1;
                while(checkr)
                {
                    checkr=0;
                    r=rand()%8+1;
                    for(int i=0;i<nt;i++)
                    {
                        if(r==index_total[i])
                            checkr=1;
                    }
                }
                cout<<"My next position is "<<r<<"."<<endl;
                t[r-1]='X';
                index_x[nx++]=r;
                index_total[nt++]=r;
                print(t);
                if(nx>=3)
                    if(checkwin(index_x,nx)==1)
                    {
                        cout<<"I win."<<endl;
                        break;
                    }
            }
        }
        else if(order==2)
        {
            while(1)
            {
                int r=rand()%8+1;
                checkr=1;
                while(checkr)
                {
                    checkr=0;
                    r=rand()%8+1;
                    for(int i=0;i<nt;i++)
                    {
                        if(r==index_total[i])
                            checkr=1;
                    }
                }
                cout<<"My next position is "<<r<<"."<<endl;
                t[r-1]='X';
                index_x[nx++]=r;
                index_total[nt++]=r;
                print(t);
                if(nx>=3)
                    if(checkwin(index_x,nx)==1)
                    {
                        cout<<"I win."<<endl;
                        break;
                    }
                if(nt==9)
                {
                    cout<<"tie"<<endl;
                    break;
                }
                cout<<"Please input next position you select: ";
                checki=1;
                while(checki)
                {
                    cin>>index;
                    checki=0;
                    for(int i=0;i<nt;i++)
                    {
                        if(index==index_total[i])
                        {
                            cout<<index<<" is already here, please input another number: ";
                            checki=1;
                        }
                    }
                }
                t[index-1]='O';
                index_o[no++]=index;
                index_total[nt++]=index;
                print(t);
                if(no>=3)
                    if(checkwin(index_o,no)==1)
                    {
                        cout<<"You win."<<endl;
                        break;
                    }
            }
        }
        cout<<"Do you want to play again?"<<endl<<"If you want to leave, please input '0'. Else, enter any positive number: ";
        cin>>check;
        cout<<"\n\n\n";
    }
    return 0;
}
void print(char t[])
{
    for(int i=0;i<9;i++)
    {
        cout<<t[i];
        if(i%3==2)
            cout<<endl;
        else
            cout<<"|";
    }
}
int checkwin(int index[],int n)
{
    int cw;
    int matric[3][3]={0};
    for(int i=0;i<n;i++)
    {
        int v=index[i]-1;
        matric[v/3][v%3]=1;
    }
    for(int i=0;i<3;i++)
    {
        cw=0;
        for(int j=0;j<3;j++)
        {
            if(matric[i][j]==1)
                cw++;
            if(cw>=3)
            {
                print_line(3*i+1,3*i+2,3*i+3);
                return 1;
            }
        }
    }
    for(int i=0;i<3;i++)
    {
        cw=0;
        for(int j=0;j<3;j++)
        {
            if(matric[j][i]==1)
                cw++;
            if(cw>=3)
            {
                print_line(1+i,3+1+i,3*2+i);
                return 1;
            }

        }
    }
    cw=0;
    for(int i=0;i<3;i++)
    {
        if(matric[i][i]==1)
            cw++;
        if(cw>=3)
        {
            print_line(1,5,9);
            return 1;
        }
    }
    cw=0;
    for(int i=0;i<3;i++)
    {
        if(matric[i][2-i]==1)
            cw++;
        if(cw>=3)
        {
            print_line(3,5,7);
            return 1;
        }
    }
    return 0;
}
void print_line(int index1,int index2,int index3)
{
    cout<<"A line formed by positions "<<index1<<", " <<index2<<" and "<<index3<<"."<<endl;
}
