#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,a;
    int x[5][5];
    for(i=0;i<5;i++)
    {
        printf("Enter row %d: ",i+1);
        for(j=0;j<5;j++)
        {

            scanf("%d",&a);
            x[i][j]=a;
        }
    }
    int rowsum=0;
    int columnsum=0;
    printf("\nRow totals: ");
    for(i=0;i<5;i++)
    {
     for(j=0;j<5;j++)
     {
         rowsum=x[i][j]+rowsum;
         if(j==4)
         {
             printf("%d ",rowsum);
             rowsum=0;
         }
     }
    }
    printf("\nColumn totals: ");
    for(j=0;j<5;j++)
    {
     for(i=0;i<5;i++)
     {
         columnsum=x[i][j]+columnsum;
         if(i==4)
         {
             printf("%d ",columnsum);
             columnsum=0;
         }
     }
    }
    return 0;
}
