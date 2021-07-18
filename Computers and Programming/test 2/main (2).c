#include <stdio.h>
#include <stdlib.h>

int main()
{
    int size;
    scanf("%d",&size);
    int matrix[size][size];
    int i,j;
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            scanf("%d",&matrix[i][j]);
        }
    }
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            printf("%d ",matrix[j][i]);
        }
        printf("\n");
    }
    return 0;
}
