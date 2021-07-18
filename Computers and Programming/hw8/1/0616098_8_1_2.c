// Binary Search
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // prototype for function time

void bubbleSort( int *data, int number );
void swap( int *ptr1, int *ptr2 );
int binarySearch( int *data, int size, int searchElement );

int main()
{
   srand(time(NULL));

   int number;
   int i;
   printf("Enter a positive integer : ");
   scanf("%d", &number);

   int *data;
   data = (int*)malloc(number * sizeof(int));

   for (i = 0; i < number; i++ )
      data[ i ] = 10 + rand() % 90; // 10-99

   printf("Data items in original order\n");

   // output original array
   for (i = 0; i < number; i++ )
      printf("%4d",data[i]);

   bubbleSort( data, number ); // bubble sort

   printf("\nData items in ascending order\n");

   // output sorted array
   for (i = 0; i < number; i++ )
      printf("%4d",data[i]);

   int searchInt; // search key

   // get input from user
   printf("\n\nPlease enter an integer value (-1 to quit): ");
   scanf("%d", &searchInt);


   // use binary search to try to find integer
   int position = binarySearch( data, number, searchInt );

   // return value of -1 indicates integer was not found
   if ( position == -1 )
      printf("\nThe integer %d was not found.\n\n", searchInt);
   else
      printf("\nThe integer %d was found in position %d.\n\n", searchInt, position);

   free(data);

   system( "pause" );

   return 0;

} // end main

void bubbleSort( int *data, int number )
{
   int a,*i,*j;
    i=data;
    j=data;
    while(*i++!=0)
    {
        for(j=data;j-data<number-(i-data);j++)
        {
            if(*j>*(j+1))
            {
                swap(j,(j+1));
            }
        }

    }
}

void swap( int *ptr1, int *ptr2 )
{
   int hold = *ptr1;
   *ptr1 = *ptr2;
   *ptr2 = hold;
}

// perform a binary search on the data
int binarySearch( int *data, int size, int searchElement )
{
   int *a,*b,*c,n=1;
   a=data;
   b=data+size;
   c=data+size/2;
   if(*c==searchElement)
   {
       n=0;
       return c-data+1;
   }
    while(n)
    {
        if(*a==searchElement)
        {
            n=0;
            return a-data+1;
        }
        else if(*b==searchElement)
        {
            n=0;
            return b-data+1;
        }
        else if(*c==searchElement)
        {
            n=0;
            return c-data+1;
        }
        if(searchElement<*c)
            {
                b=c;
                size=size/2;
                c=(a+size);
            }
        else if(searchElement>*c)
        {
            a=c;
            size=size/2;
            c=(b-size);
        }
        if(b-a<=1)
            break;
    }
    if(n==1)
        return -1;
}

