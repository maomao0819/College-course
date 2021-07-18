#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Input: ");
    char a[100];
    scanf("%s",&a);
    int i,b=0,d=0;
    char c[100];
    int j=0;
    for(i=0;i<100;i++)
    {
        if('A'<=a[i]&&a[i]<='Z')
           {
               c[b++]=a[i];
           }
        else if('a'<=a[i]&&a[i]<='z')
           {
               c[b++]=a[i];
           }
        else if('0'<=a[i]&&a[i]<='9')
           {
               c[b++]=a[i];
           }
           else if(a[i]==0)
            break;
    }
    int e=0,f;
    for(i=0;i<b/2;i++)
    {
        if('0'<=c[i]&&c[i]<='9')
           {
               if(c[i]==c[b-1-i])
               e++;
           }
        else if('a'<=c[i]&&c[i]<='z')
        {
            if(c[i]==c[b-1-i]||c[i]-32==c[b-1-i])
               e++;
        }
        else if('A'<=c[i]&&c[i]<='Z')
        {
            if(c[i]==c[b-1-i]||c[i]+32==c[b-1-i])
               e++;
        }
            f=e/(b/2);
    }
    if(f>0)
        printf("Yes, it is a palindrome");
    if(f==0)
        printf("No, it is not a palindrome");
    return 0;
}
