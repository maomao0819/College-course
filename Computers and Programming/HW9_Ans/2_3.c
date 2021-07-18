#include<stdio.h>
#include<stdlib.h>

struct day {
    int yy, mm, dd; /* 年、月、日 */
};

struct data {
    char name[20];  /* 姓名 */
    struct day birthday;  /* 生日 */
    int chi, math, eng;   /* 國文、數學 與 英文成績 */
};

struct data student[8] = {
	{  "Marry Hu", {87, 2, 3},   89, 90, 79},
	{  "Tom Chen", {88, 12, 13}, 79, 69, 88},
    {  "Billy Wu", {87, 1, 30},  81, 54, 66},
    {  "John Hsu", {87, 7, 22},  69, 49, 20},
    { "Tim Huang", {87, 3, 8},   90, 62, 83},
    {"Marry Chen", {88, 5, 27},  78, 93, 91},
    { "Tomas Chu", {88, 5, 18},  80, 50, 68},
    {  "Ann Wang", {87, 9, 21},  66, 79, 78}
};


void happy_birthday(struct data student[], int);
int lowest_grade(struct data student[]);

int main(void)
{
        int max;
        int m;
        printf("Please enter the month:");
        scanf("%d", &m);
        happy_birthday(student, m);
        lowest = lowest_grade(student);
        printf("The student who has the lowest average score is: %s\n", student[max].name);
        return 0;
}
/*列出壽星*/
void happy_birthday(struct data student[], int month)
{
        int i;
        printf("The Longevity god on the month you input are: \n");
        for(i=0;i<8;i++)
        {
                if(student[i].birthday.mm==month)
                {
                   printf("Name: %s\n",student[i].name);
                   printf("Birthday: %d/%d/%d\n",student[i].birthday.yy,student[i].birthday.mm,student[i].birthday.dd);
                   printf("Math score is: %d\n",student[i].math);
                   printf("=================\n");
                }

        }
}
/*找出各科平均分數最低的那位同學，並回傳其索引值*/
int lowest_grade(struct data student[])
{
        int i,temp2;
        struct data temp;
        temp=student[0];
        for(i=0;i<8;i++)
        {
                if((student[i].chi+student[i].math+student[i].eng)/3<(temp.chi+temp.math+temp.eng)/3)
                {
                        temp=student[i];
                        temp2=i;
                }
        }
        return temp2;
}


