#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Input: ");
    char a[5];
    scanf("%s",&a);
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(a[j]<a[j+1])
            {
                char b;
                b=a[j];
                a[j]=a[j+1];
                a[j+1]=b;
            }
        }
    }
    if(a[0]==a[1]&&a[3]==a[4]&&a[2]==a[1]&&a[2]!=a[3])
            printf("Yes, is a full house");
    else if(a[0]==a[1]&&a[3]==a[4]&&a[2]==a[3]&&a[2]!=a[1])
            printf("Yes, is a full house");
    else
        printf("No, is not a full house");
    return 0;
}
