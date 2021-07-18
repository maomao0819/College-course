# Week12 Homework9
## Synopsis 
1. Please use struct to store the coordinate
   of points, and calculate distance of two
   points.
   Hint: you can use the function prototype:
   double dist(your_struct_of_point,your_struct_of_point);
2&3. (use 2_3.c) Leon just started a home
     teaching group with eight students. The
     information of students contains name,
     birthday, grades of chinese, math, and
     english. Please implement the function
     happy_birthday to help Leon know when his
     students will have birthday.
     ¡´ void happy_birthday(struct data student[], int month);
     Please implement the function min_grade 
     to help Leon know which student he should spend more time on.
     ¡´ int min_grade(struct data student[]);
     ¡´ It will return the index value of the
     student in data, which has the lowest average grades.
4. Write a program to calculate the score of sequence
   containing ¡¥O¡¦ and ¡¥X¡¦
   ¡´¡¥O¡¦: correct answer;¡¥X¡¦: wrong answer
   ¡´ The score of each problem calculated by the number of
   consecutive ¡¥O¡¦s appeared previously. The score starts
   with 1. Once a ¡¥X¡¦ is encountered, the score will be reset.
   ¡´ Score of ¡§OOXXOXXOOO¡¨ is 10 -> 1+2+0+0+1+0+0+1+2+3
   ¡´ The input sequence length L , where 0 < L <= 80.
5. B2-Sequence: a sequence of positive
   integers 1 ? b1 < b2 < b3 . . . such that
   all pairwise sums bi + bj, where i ? j, are different
   Input sequence length = N, 2 <= N <= 100
   Numbers in sequence = bis, bis <= 10000
6. Write a program to solve a linear equation with 1 variable x.
   ¡´ The input will be an equation line with:
   ¡³ No parenthesis
   ¡³ Length: at most 255 characters
   ¡³ No blank character
   ¡³ Always use the lower-case character¡¥x¡¦
   ¡³ Coefficients: [0,1000](inclusive)
   ¡´ If S is the solution, output ?S?(the¡§floor¡¨of S)
   ¡´ No solution: output ¡¥IMPOSSIBLE¡¦
   ¡´ Infinite solution: output ¡¥IDENTITY¡¦
## Contributor
Ping-Mao, Huang 
