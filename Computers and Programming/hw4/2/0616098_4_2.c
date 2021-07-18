#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Enter a positive Integer: ");
    int number;
    scanf("%d",&number);
    printf("%d!=",number);
    int x;
    long long a=1;
    if(number==0)
        printf("1");
    else
        {
    for(x=1;x<=number;x++)
    {
        a=a*x;
    }
    printf("%lld",a);
        }
    return 0;
}
