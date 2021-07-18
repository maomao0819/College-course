#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Enter a date (mm/dd/yyyy): ");
    int month,day,year;
    scanf("%d/%d/%d",&month,&day,&year);
    printf("You entered the date %4d%.2d%.2d",year,month,day);
    return 0;
}
