#include <stdio.h>
#include <stdlib.h>

int main()
{
    int matrix1[3][3]={{1,2,4},{1,5,3},{4,2,3}};
    int matrix2[3][3]={{2,5,2},{4,2,3},{6,2,1}};
    int sum[3][3];
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            sum[i][j]=matrix1[i][j]+matrix2[i][j];
            printf("%d ",sum[i][j]);
            if(j==2)
                printf("\n");
        }
    }

    return 0;
}
