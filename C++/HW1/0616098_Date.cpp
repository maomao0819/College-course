#include <iostream>
#include "0616098_Date.h"

using namespace std;


    Date::Date(int day, int month, int year)
    {
        setDay(day);
        setMonth(month);
        setYear(year);
    }
    Date::~Date(){}


    /*Get function for accessing private member*/
    int Date::getDay()
    {
        return day;
    }
    int Date::getMonth()
    {
        return month;
    }
    int Date::getYear()
    {
        return year;
    }

    /*Set function for updating private member*/
    void Date::setDay(int day)
    {
        this->day=day;
    }
    void Date::setMonth(int month)
    {
        this->month=month;
    }
    void Date::setYear(int year)
    {
        this->year=year;
    }

    /*A Function that returns the date after a given date
        For e.g-

        today is 8/3/2018 (Day/Month/Year)
        DateAfter(3) should return a date of 11/3/2018 */
    Date Date::DateAfter(int days)
    {
        int d=day+days;
        int m=month;
        int y=year;
        while(d>numberOfDays())
        {

            d-=numberOfDays();
            m++;
        }
        while(m>12)
        {
            m-=12;
            y++;
        }
        return Date(d,m,y);
    }

    /*A Function that returns the date after a given date
        For e.g-

        today is 8/3/2018 (Day/Month/Year)
        DateBefore(3) should return a date of 5/3/2018 */
    Date Date::DateBefore(int days)
    {
        int d=day-days;
        int m=month;
        int y=year;;
        while(day<1)
        {
            m--;
            d-=numberOfDays();
        }
        while(m<1)
        {
            m+=12;
            y--;
        }
        return Date(d,m,y);
    }

    int Date::week(int d)
    {
        int y=year;
        int m=month;
        if(m==1||m==2)
        {
            y--;
            m+=12;
        }
        return (y+y/4-y/100+y/400+(13*m+8)/5+d)%7;
    }

    /*A Function that returns the day of a date
        For e.g-

        if the date is 8/3/2018, then the dayOfWeek() function
        should return "Thursday"
    */

    string Date::dayOfWeek()
    {
        switch(week(this->day))
        {
            case 0:
                return "Sunday";
                break;
            case 1:
                return "Monday";
                break;
            case 2:
                return "Tuesday";
                break;
            case 3:
                return "Wednesday";
                break;
            case 4:
                return "Thursday";
                break;
            case 5:
                return "Friday";
                break;
            case 6:
                return "Saturday";
                break;
        }
    }

    /* A Function to return the number of days in
        Current Month.

        Month Number     Name        Number of Days
        0                January     31
        1                February    28 (non-leap) / 29 (leap)
        2                March       31
        3                April       30
        4                May         31
        5                June        30
        6                July        31
        7                August      31
        8                September   30
        9                October     31
        10               November    30
        11               December    31*/
    int Date::numberOfDays()
    {
        switch(month)
        {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                return 31;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                return 30;
                break;
            case 2:
                if((year%4==0&&year%100!=0)||year%400==0)
                    return 29;
                else
                    return 28;
                break;
        }
    }

    /* Function to print a calendar of the current month.
    Just like what you see on a calendar. An example is like

   --------------March--------------
   Sun  Mon  Tue  Wed  Thu  Fri  Sat
                        1    2    3
    4    5    6    7    8    9   10
   11   12   13   14   15   16   17
   18   19   20   21   22   23   24
   25   26   27   28   29   30   31

   */
    void Date::printMonthCalendar()
    {
        switch(month)
        {
            case 1:
                cout<<"-------------January-------------"<<endl;
                break;
            case 2:
                cout<<"-------------February------------"<<endl;
                break;
            case 3:
                cout<<"--------------March--------------"<<endl;
                break;
            case 4:
                cout<<"--------------April--------------"<<endl;
                break;
            case 5:
                cout<<"---------------May---------------"<<endl;
                break;
            case 6:
                cout<<"---------------June--------------"<<endl;
                break;
            case 7:
                cout<<"---------------July--------------"<<endl;
                break;
            case 8:
                cout<<"--------------August-------------"<<endl;
                break;
            case 9:
                cout<<"------------September-------------"<<endl;
                break;
            case 10:
                cout<<"-------------October-------------"<<endl;
                break;
            case 11:
                cout<<"-------------November------------"<<endl;
                break;
            case 12:
                cout<<"-------------December------------"<<endl;
                break;
        }
        cout<<"Sun  Mon  Tue  Wed  Thu  Fri  Sat"<<endl;
        int i;
        for(i=0;i<week(1)-1;i++)
        {
            cout<<"     ";
        }
        for(i=1;i<=numberOfDays();i++)
        {
            if(i<10)
                cout<<" ";
            cout<<i<<"   ";
            if(week(i)==0)
                cout<<endl;
        }
    }
