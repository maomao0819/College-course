#include <stdio.h>
#include <stdlib.h>

int main()
{
    int size1;
    scanf("%d",&size1);
    int matrix1[size1][size1];
    int *p=matrix1;
    int i,j;
    for(i=0;i<size1;i++)
    {
        for(j=0;j<size1;j++)
           {
                scanf("%d",&matrix1[i][j]);
           }
    }
    int size2;
    scanf("%d",&size2);
    int matrix2[size2][size2];
    int *q=matrix2;
    for(i=0;i<size2;i++)
    {
        for(j=0;j<size2;j++)
           {
                scanf("%d",&matrix2[i][j]);
           }
    }
    int k,l;
    int a=size1-size2+1;
    int test;
    for(k=0;k<size1-size2+1;k++)
    {
    for(l=0;l<size1-size2+1;l++)
    {
         test=0;
         for(i=k;i<size2+k;i++)
         {
              for(j=l;j<size2+l;j++)
              {
                   if(matrix1[i][j]==matrix2[i-k][j-l])
                      test++;
                    if(test==size2*size2)
            {
             printf("%d",i-size2+1);
             printf(" %d",j-size2+1);
           }
              }
         }



    }
    }
    return 0;
}
