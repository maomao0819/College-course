#include <stdio.h>
#include <stdlib.h>

int main()
{
    char a[40];
    printf("Your input: ");
    scanf("%s/n",&a);
    printf("ASCII: %d%d%d%d",a[0],a[1],a[2],a[3]);
    return 0;
}
