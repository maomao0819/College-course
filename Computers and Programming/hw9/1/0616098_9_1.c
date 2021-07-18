#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct coordinate
{
    int x;
    int y;
};
double dist(struct coordinate a,struct coordinate b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int main()
{
    struct coordinate a,b;
    struct coordinate *c=&a;
    printf("Enter the coordinate of first point in x,y:");
    scanf("%d,%d",&c->x,&c->y);
    printf("\nEnter the coordinate of second point in x,y:");
    scanf("%d,%d",&b.x,&b.y);
    printf("\nThe distance of two points is: %f\n",dist(a,b));
    return 0;
}
