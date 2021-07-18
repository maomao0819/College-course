#include <stdio.h>
#include <math.h>

typedef struct {
	double x;
	double y;
} Point;

double dist(Point, Point);

int main()
{
	Point p, q;
	printf("Enter the coordinate of first point in x,y: \n");
	scanf("%lf,%lf", &p.x, &p.y);

	printf("\nEnter the coordinate of second point in x,y: \n");
	scanf("%lf,%lf", &q.x, &q.y);

	printf("\nThe distance of two points is: %lf\n", dist(p, q));

	return 0;
}

double dist(Point a, Point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}	
