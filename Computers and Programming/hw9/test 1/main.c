#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct coordinate
{
    int x;
    int y;
}Coordinate;
double dist(Coordinate a,Coordinate b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int main()
{
    Coordinate a,b;
    Coordinate *c=&a;
    printf("Enter the coordinate of first point in x,y:");
    scanf("%d,%d",&c->x,&c->y);
    printf("Enter the coordinate of second point in x,y:");
    scanf("%d,%d",&b.x,&b.y);
    printf("%f\n",dist(a,b));
    return 0;
}
