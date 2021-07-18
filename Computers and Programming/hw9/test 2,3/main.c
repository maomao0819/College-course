#include<stdio.h>
#include<stdlib.h>

typedef struct day {
    int yy, mm, dd; /* るら */
}Day;

typedef struct data {
    char name[20];  /* ﹎ */
    Day birthday;  /* ネら */
    int chi, math, eng;   /* 瓣ゅ计厩 籔 璣ゅΘ罿 */
}Data;

Data student[8] = {
	{  "Marry Hu", {87, 2, 3},   89, 90, 79},
	{  "Tom Chen", {88, 12, 13}, 79, 69, 88},
    {  "Billy Wu", {87, 1, 30},  81, 54, 66},
    {  "John Hsu", {87, 7, 22},  69, 49, 20},
    { "Tim Huang", {87, 3, 8},   90, 62, 83},
    {"Marry Chen", {88, 5, 27},  78, 93, 91},
    { "Tomas Chu", {88, 5, 18},  80, 50, 68},
    {  "Ann Wang", {87, 9, 21},  66, 79, 78}
};


void happy_birthday(Data student[], int);
int lowest_grade(Data student[]);

int main(void)
{
        int lowest;
        int m;
        printf("Please enter the month:");
        scanf("%d", &m);
        happy_birthday(student, m);
        lowest = lowest_grade(student);
        printf("The student who has the lowest average score is: %s\n", student[lowest].name);
        return 0;
}
/*关琍*/
void happy_birthday(Data student[], int month)
{
    int i;
    for(i=0;i<8;i++)
    {
        if(student[i].birthday.mm==month)
            printf("%s\n%d/%d/%d/\n%d\n",student[i].name,student[i].birthday.yy,student[i].birthday.mm,student[i].birthday.dd,student[i].math);
    }
}
/*тキАだ计程ê厩肚ㄤま*/
int lowest_grade(Data student[])
{
    int i;
    int min=student[0].chi+student[0].math+student[0].eng;
    int mark=0;
    for(i=1;i<8;i++)
    {
        int sum=student[i].chi+student[i].math+student[i].eng;
        if(sum<min)
        {
            mark=i;
            min=sum;
        }
    }
    return mark;
}
