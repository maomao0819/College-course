#include<stdio.h>
#include<stdlib.h>
typedef struct Data
{
    int value;
    int index;
}d;
d data[300000];
int compare(const void* a, const void* b)
{
    d* ptr1 = (d*)a;
    d* ptr2 = (d*)b;
    int value1 = ptr1->value;
    int value2 = ptr2->value;
    int index1 = ptr1->index;
    int index2 = ptr2->index;
    if(value1 < value2) return 1;
    else if(value1 == value2 && index1 > index2)    return 1;
    return -1;
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++)
    {
        data[i].index = i;
        scanf("%d", &data[i].value);
    }
    qsort(data, n, sizeof(d), compare);
    /*for(int i = 0; i < n; i++)
    {
        printf("%d ", data[i].value);
    }
    printf("\n");
    for(int i = 0; i < n; i++)
    {
        printf("%d ", data[i].index);
    }
    printf("\n");*/
    for(int i = 0; i < m; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        for(int j = 0; j < n; j++)
        {
            if(data[j].index + 1 <= r && data[j].index + 1 >= l)
            {
                printf("%d\n", data[j].index + 1);
                break;
            }
        }
    }
}
