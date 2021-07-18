#include <stdio.h>
#include <stdlib.h>
void printstar(int a)
{
    int i,j;
    for(i=1;i<=a;i++)
    {
        printf("\n");
        for(j=1;j<=a;j++)
        {
            printf("* ");
        }
    }
}
int main(void)
{
    printf("Please enter the length of side: ");
    int a;
    scanf("%d",&a);
    printstar(a);
    printf("\n");
    return 0;
}
