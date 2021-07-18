#include <stdio.h>
#include <stdlib.h>

int f(int n);
int main(){
    int n;

    printf("Enter a non-negative integer n (0~20): ");
    scanf("%d", &n);
    printf("The nth Fibonacci number is %d.\n", f(n));

    system("PAUSE");
    return 0;
}

int f(int n){
    if(n==0||n==1)
        return n;
   else
    return f(n-1)+f(n-2);
}
