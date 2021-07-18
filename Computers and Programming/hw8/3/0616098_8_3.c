#include <stdio.h>
#include <stdlib.h>
int **matricMultiplication(int*,int*);
int z[9]={0};
int main()
{
    printf("Please enter the first matrix:");
    int x[9];
    int *p;
    p=x;
    for(p=x;p<x+9;p++)
    {
        scanf("%d",p);
    }
    int y[9];
    printf("\n\nPlease enter the second matrix:");
    int *q;
    q=y;
    for(q=y;q<y+9;q++)
    {
        scanf("%d",q);
    }
    matricMultiplication(x,y);
    printf("\n\nThe result of multiplication of two matrices:\n");
    int i;
    for(i=0;i<3;i++)
        {
           printf("%d %d %d\n",z[i],z[i*3+1],z[i*3+2]);
        }
    return 0;
}
int **matricMultiplication(int *p,int *q)
{
    int i,j;
    for(i=0;i<9;i++)
        {
         for(j=0;j<3;j++)
            {
                  z[i]=z[i]+*(p+j+(i/3)*3) * *(q+j*3+i%3);
            }
        }
    return 0;
}
