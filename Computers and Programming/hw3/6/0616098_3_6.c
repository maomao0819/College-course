#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j;
    for(i=1;i<10;i++)
    {
        for(j=1;j<10;j++)
        {
            printf("%02d * %02d = %02d\n",i,j,j*i);
        }
    }
    return 0;
}
