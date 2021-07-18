#include <stdio.h>
#include <stdlib.h>

int main()
{
    int b;
    while(1)
    {
    printf("Red-Fish:The number is ");
    scanf("%d",&b);
    if(b==-1)
        {
            printf("I don't know,I quit.");
            return 0;
        }
    if(b%2!=0)
        {
        printf("Wen-JIe:The answer is odd.");
        printf("\n\n");
        }
    if(b%2==0)
        {
        printf("Wen-JIe:The answer is even.");
        printf("\n\n");
        }
    }
    return 0;
}
