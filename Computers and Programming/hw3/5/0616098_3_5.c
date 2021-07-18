#include <stdio.h>
#include <stdlib.h>

int main()
{
    while(1)
    {
        printf("Please enter your month: ");
        int a;
        scanf("%d",&a);
        switch(a)
        {

            case 1:
            printf("January\n");
            break;
            case 2:
            printf("February\n");
            break;
            case 3:
            printf("March\n");
            break;
            case 4:
            printf("April\n");
            break;
            case 5:
            printf("May\n");
            break;
            case 6:
            printf("June\n");
            break;
            case 7:
            printf("July\n");
            break;
            case 8:
            printf("August\n");
            break;
            case 9:
            printf("September\n");
            break;
            case 10:
            printf("October\n");
            break;
            case 11:
            printf("November\n");
            break;
            case 12:
            printf("December\n");
            break;
            case 0:
            break;
            default:
            printf("Invalid Input. Please try again...\n");
            break;
        }
        if (a==0)
             {
            printf("Goodbye");
            return 0;
             }
    }
    return 0;
}
