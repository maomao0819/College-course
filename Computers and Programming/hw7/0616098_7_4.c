#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    printf("Please input two string: ");
    char a[100];
    char b[100];
    scanf("%s %s",&a,&b);
    int c=0;
    int d=0,e=0,f=0,g=0;
    int i,j,k;
    for(i=0;i<100;i++)
    {
        if(a[i]!=0)
            d++;
        else
            break;
    }
    for(i=0;i<100;i++)
    {
        if(b[i]!=0)
            e++;
        else
            break;
    }
    char x[d];
    for(i=0;i<d;i++)
    {
        x[i]=a[i];
    }
    for(i=0;i<d;i++)
    {
        for(j=0;j<e;j++)
        {
            if(a[i]==b[j])
            {
                for(k=0;k<d;k++)
                {
                    if(a[i+k]==b[j+k])
                        c++;
                    if(c==d)
                    {
                        f=1;
                    goto q;
                    }
                }
                c=0;
            }
        }
    }
    q:
    if(f>0)
        printf("Output: Yes");
    else
        printf("Output: No");
    return 0;
}

