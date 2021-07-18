#include <stdio.h>
#include <stdlib.h>
int cha(int a);
int main()
{
    int b=1;
    while(b)
    {
        char a[10];
        int i;
        for(i=0;i<10;i++)
            a[i]=0;
        scanf("%s",&a);
        if(a[0]<=48)
            break;
        int sum=0;
        int len=0;
        for(i=0;i<10;i++)
            {
            if(a[i]<='9'&&a[i]>='0')
            {
                sum=sum+a[i];
                len++;
            }
        }
        int s=0;
        s=sum-48*len;
        int r=0;
        r=cha(s);
        printf("%d\n",r);
    }
    return 0;
}
int cha(int a)
{
    if(a<10)
        return a;
    int su=a%10+a/10;
    return cha(su);
}
