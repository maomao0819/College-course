#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Please enter the number of correct answer: ");
    int a;
    scanf("%d",&a);
    printf("The score is: ");
    if(a<=8)
        printf("%d",a*8);
    if(a>8)
    {
        int b=64+6*(a-8);
        printf("%d",b);
    }
    return 0;
}
