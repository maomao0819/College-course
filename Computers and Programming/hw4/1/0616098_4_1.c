#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Enter a positive integer(3-90): ");
    int number;
    scanf("%d",&number);
    unsigned long int i=1;
    unsigned long int j=1;
    printf("\n1 1");
    int x;
    for(x=0;x<number-2;x++)
    {
        if(x%2==1)
        {
            i=i+j;
            printf(" %u",i);
        }
        else
        {
            j=i+j;
            printf(" %u",j);
        }
    }
    return 0;
}
