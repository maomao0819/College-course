#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Please enter serveral positive integers (end with 0):" );
    int a;
    int b=0;
    float total=0;
    float average;
    while(1)
    {
        scanf("%d",&a);
        if(a>0)
        {
            total=total+a;
            b++;
        }
        else
        {
             average=total/b;
            printf("The average is %.2f",average);
            return 0;
        }
    }

}
