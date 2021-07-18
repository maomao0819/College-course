#include <iostream>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int search(int data[][100],int n,int m,int target,int &t_row,int &t_col); 
int main(int argc, char** argv) {
	int n,m;
	cout<<"Please input n and m: ";
	cin>>n>>m;
	cout<<"Please input the elements of matrix n*m by row major:\n";
	int a[n][100]={0};
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			cin>>a[i][j];
		}
	}
	while(EOF)
	{
		int s;
		int mark=1;
		cout<<"Please input a target to search (<ctrl>-d to exit):";
		cin>>s;
		if(s==!EOF)
			break;
		int row=0,col=0;
		int check=search(a,n,m,s,row,col);
		if(check)
			cout<<"At row "<<row<<" and column "<<col<<"."<<endl;
		else
			cout<<"Not found."<<endl;
	}
	return 0;
}
int search(int data[][100],int n,int m,int target,int &t_row,int &t_col)
{
	for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
			{
				if(data[i][j]==target)
				{
					t_row=i;
					t_col=j;
					return 1;
				}	
			}
		}
	return 0;
}
