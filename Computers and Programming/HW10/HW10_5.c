#include <stdio.h>
#define STUDENTS 3
#define EXAMS 4
/* function prototypes */
void minimum( int grades[][ EXAMS ], int pupils, int tests );
void maximum( int grades[][ EXAMS ], int pupils, int tests );
void average( int grades[][ EXAMS ], int pupils, int tests );
void printArray( int grades[][ EXAMS ], int pupils, int tests );
void printMenu( void );
int main()
{
   /* pointer to a function that takes as parameters a
      two-dimensional array and two integer values */
   void ( *processGrades[ 4 ] )( int [][ EXAMS ], int, int )
                      = { printArray, minimum, maximum, average};
   int choice = 0; /* menu choice */
   /* array of student grades */
   int studentGrades[ STUDENTS ][ EXAMS ] = { { 77, 68, 86, 73 },
                                              { 96, 87, 89, 78 },
                                              { 70, 90, 86, 81 } };
   /* loop while user does not choose option 4 */
   while ( choice != 4 ) {
      /* display menu and read user's choice */
      do {
         printMenu();
         scanf( "%d", &choice );
      } while ( choice < 0 || choice > 4 ); /* end do...while */
      /* pass choice into the array */
      if ( choice != 4 ) {
         ( *processGrades[ choice ] )( studentGrades, STUDENTS, EXAMS );
      } /* end if */
      else {
         printf( "Program Ended.\n" );
      } 
   } 
   return 0;
} 

void minimum( int grades[][ EXAMS ], int pupils, int tests )
{
   
}

void maximum( int grades[][ EXAMS ], int pupils, int tests )
{

}

void average( int grades[][ EXAMS ], int pupils, int tests )
{
   
} 

void printArray( int grades[][ EXAMS ], int pupils, int tests )
{
   
} 
void printMenu( void )
{
   printf( "\n\tEnter a choice:\n"
          "\t  0  Print the array of grades\n"
          "\t  1  Find the minimum grade\n"
          "\t  2  Find the maximum grade\n"
          "\t  3  Print the average on all"
          " tests for each student\n"
          "\t  4  End program\n"
          "\t? " );
} 
