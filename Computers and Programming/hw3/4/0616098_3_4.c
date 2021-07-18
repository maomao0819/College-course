#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Please enter your gender: ");
    int a;
    scanf("%d",&a);
    printf("Please enter your age: ");
    int b;
    scanf("%d",&b);
    if(a==1)
    {
        if(b>=18)
            printf("You are marriageable.");
        else
            printf("You are NOT marriageable.");
    }
    if(a==2)
    {
        if(b>=16)
            printf("You are marriageable.");
        else
            printf("You are NOT marriageable.");
    }
    return 0;
}
