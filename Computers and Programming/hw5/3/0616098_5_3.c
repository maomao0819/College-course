#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Input a integer X (0 <= X < 2147483647): ");
    int a;
    scanf("%d",&a);
    int i=0;
    int b[10];
    for(i=0;i<10;i++)
        {
           b[i]=0;
        }

    int x;
    while(1)
    {
        x=a%10;
        switch(x)
        {
        case 0:
        b[0]++;
        break;
        case 1:
        b[1]++;
        break;
        case 2:
        b[2]++;
        break;
        case 3:
        b[3]++;
        break;
        case 4:
        b[4]++;
        break;
        case 5:
        b[5]++;
        break;
        case 6:
        b[6]++;
        break;
        case 7:
        b[7]++;
        break;
        case 8:
        b[8]++;
        break;
        case 9:
        b[9]++;
        break;
        }
        a=a/10;
        if(a==0)
        break;
    }
for(i=0;i<10;i++)
    {
        printf("%d : %d\n",i,b[i]);
    }
    return 0;
}
