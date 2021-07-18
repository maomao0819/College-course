#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Input : ");
    char a[80];
    scanf("%s",&a);
    int i;
    int b=0,score=0;
    for(i=0;i<80;i++)
    {
        if(a[i]=='O')
            b++;
        else
            b=0;
        score+=b;
    }
    printf("Output: %d",score);
    return 0;
}
