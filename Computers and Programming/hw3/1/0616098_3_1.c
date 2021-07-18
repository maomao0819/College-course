#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Input 3 integers(seperate each with spaces): ");
    int i,j,k;
    scanf("%d %d %d",&i,&j,&k);
    if(i>j)
    {
        if(j>k)
            printf("%d %d %d",i,j,k);
        else
        {
            if(i>k)
                printf("%d %d %d",i,k,j);
            else
                printf("%d %d %d",k,i,j);
        }

    }
    else
    {
        if(i>k)
            printf("%d %d %d",j,i,k);
        else
        {
            if(j>k)
                printf("%d %d %d",j,k,i);
            else
                printf("%d %d %d",k,j,i);
        }
    }
    return 0;
}
