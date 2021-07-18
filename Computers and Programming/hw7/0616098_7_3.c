#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Enter first string: ");
    char a[100];
    scanf("%s",&a);
    printf("Enter second string: ");
    char b[100];
    scanf("%s",&b);
    char c[200];
    int i;
    int j=0;
    for(i=0;i<100;i++)
    {
        if(a[i]!=0)
        {
          c[j]=a[i];
          j++;
        }
        else
            break;
    }
    for(i=0;i<100;i++)
    {
        if(b[i]!=0)
        {
          c[j]=b[i];
          j++;
        }
        else
            break;
    }
    printf("After concatenation: %s",c);

    return 0;
}
