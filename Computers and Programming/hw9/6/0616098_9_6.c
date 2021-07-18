#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Input: ");
    char a[255];
    scanf("%s",&a);
    printf("%s\n",a);
    int x=0,c=0;
    int i;
    int mark;
    for(i=0;i<255;i++)
        if(a[i]=='=')
           mark=i;
           printf("\n%d\n",mark);
    char opperation;
    for(i=0;i<255;i++)
        printf("%c",a[i]);
    //for(i=0;i<mark;i++)
    //{

    //}
    //for(i=mark+1;i<255;i++)
    //{

    //}
    return 0;
}
