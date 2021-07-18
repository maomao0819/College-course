#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Please, enter the product number and the quantity sold out for one day (end with 0):\n");
    float total;
    while(1)
    {
        int a,b;
        scanf("%d",&a);

        if(a==0)
        {
            break;
        }

        else
        {
           scanf("%d",&b);
        switch(a)
        {
    case 1:
        total=total+2.98*b;
        break;
    case 2:
        total=total+4.50*b;
        break;
    case 3:
        total=total+9.98*b;
        break;
    case 4:
        total=total+4.49*b;
        break;
    case 5:
        total=total+6.87*b;
        break;
        }
        }
    }
    printf("The total retail value of all product sold for one week :%.2f",total*7);
    return 0;
}
