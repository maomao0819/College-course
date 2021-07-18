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
      printf("The integer %d was not found.\n\n", searchInt);
   else
      printf("The integer %d was found in position %d.\n\n", searchInt, position);

   free(data);

   system( "pause" );

   return 0;

} // end main

void bubbleSort( int *data, int number )
{

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
    
}

