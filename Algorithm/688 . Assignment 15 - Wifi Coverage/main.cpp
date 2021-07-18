#include <iostream>

using namespace std;

void quicksort(int a1[], int a2[], int le, int ri);
int partition(int a1[], int a2[], int le, int ri);
int main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int w,n;
	cin>>w>>n;
	int x[n],r[n];
	int wifi_str[n];
	int wifi_end[n];
	for(int i=0;i<n;i++)
    {
        cin>>x[i]>>r[i];
        wifi_str[i]=x[i]-r[i];
        wifi_end[i]=x[i]+r[i];
    }
	quicksort(wifi_str,wifi_end,0,n);
	int posi=0;
	int num=0;
    int mark;
	for(int i=0;i<n;i++)
    {
        if(wifi_str[i]>posi||posi>=w)
            break;
        mark=0;
        int tempposi=wifi_end[i];
        while(wifi_str[i]<=posi&&posi<w)
        {
            if(tempposi<wifi_end[i])
                tempposi=wifi_end[i];
            i++;
            mark=1;
        }
        i-=mark;
        posi=tempposi;
        num+=mark;
    }
    if(w==0)
        num=1;
    if(posi<w)
        num=-1;
    cout<<num;
	return 0;
}
void quicksort(int a1[], int a2[], int le, int ri)
{
    if(le<ri)
    {
        int p=partition(a1, a2, le, ri);
        quicksort(a1, a2, le, p-1);
        quicksort(a1, a2, p+1, ri);
    }
}
int partition(int a1[], int a2[], int le, int ri)
{
    int pivot=a1[ri];
    int p=le-1;
    int temp;
    for(int i=le;i<ri;i++)
    {
        if(a1[i]<=pivot)
        {
            p++;
            temp=a1[i];
            a1[i]=a1[p];
            a1[p]=temp;
            temp=a2[i];
            a2[i]=a2[p];
            a2[p]=temp;
        }
    }
    temp=a1[p+1];
    a1[p+1]=a1[ri];
    a1[ri]=temp;
    temp=a2[p+1];
    a2[p+1]=a2[ri];
    a2[ri]=temp;
    return p+1;
}
