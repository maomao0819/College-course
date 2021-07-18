#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct time{
  int hr;
  int min;
}TIME;
typedef struct train{
  int num;
  char dest[20];
  TIME depart;
  TIME arrive;
  struct train *next;
}TRAIN;
TRAIN *head = NULL;
void arriving();//Add the train just arrived to the table
void leaving();//Remove the train just left
void search();//Search for certain train by its number
void insert();//Insert a train
void del();//Delete a train
void printTitle();
void printTable(TRAIN *list);
TRAIN *add_to_list(TRAIN *list,int n,char d[],int dth,int dtm,int ath,int atm);
TRAIN *search_list(TRAIN *list,int n);
TRAIN *delete_from_list(TRAIN *list,int n);
int mark=1;
int main()
{
  int func=1;
  while(func)
  {
      printf("Please enter the instuction: ");
      scanf("%d",&func);
      switch(func)
      {
          case 0:
              printf("\n       *** END ***\n");
              break;
          case 1:
              arriving();
              break;
          case 2:
              leaving();
              break;
          case 3:
              search();
              break;
          case 4:
              insert();
              break;
          case 5:
              del();
              break;
          default:
              printf("    ***Wrong command***\n");
      }
  }
  return 0;
}
TRAIN *newtrain(int n,char d[],int dth,int dtm,int ath,int atm)
{
 TRAIN *new_train;
 new_train = (TRAIN*)malloc(sizeof(TRAIN));
 if (new_train == NULL)
 {
     printf("Error: malloc failed in add_to_list\n");
     exit(EXIT_FAILURE);
 }
 new_train->num = n;
 strcpy(new_train->dest,d);
 new_train->depart.hr = dth;
 new_train->depart.min = dtm;
 new_train->arrive.hr = ath;
 new_train->arrive.min = atm;
 return new_train;
}
TRAIN *add_to_list(TRAIN *list,int n,char d[],int dth,int dtm,int ath,int atm)
{
TRAIN *new_train;
 new_train=newtrain(n,d,dth,dtm,ath,atm);
 new_train->next = list;
 return new_train;
}
void printTitle()
{
    printf("Train number\tDestination\tDeparture Time\tArrival Time\n");
}
void arriving()
{
   printf("---Please enter the arriving train information---");
   printf("\nTrain number: ");
   int tn;
   scanf("%d",&tn);
   printf("Destination: ");
   char d[20];
   scanf("%s",d);
   printf("Departure time: ");
   int dth,dtm;
   scanf("%d:%d",&dth,&dtm);
   printf("Arrival time: ");
   int ath,atm;
   scanf("%d:%d",&ath,&atm);
   head=add_to_list(head,tn,d,dth,dtm,ath,atm);
   printf("\n\n");
   printTitle();
   printTable(head);
   printf("\n\n\n");
}
void leaving()
{
  printf("\n\n\n");
  TRAIN *temp,*follow;
  temp = head;
  follow=temp;
  int c=1;
  if(temp == NULL)
  {
      printf("There is no train available for departure currently \n");
  }
  else
  {
      while(c)
      {
          if(temp->next!=NULL)
          {
              follow=temp;
              temp=temp->next;
          }
          else if(temp->next==NULL)
          {
              if(follow==temp)
                  follow=NULL;
              free(temp);
              if(follow!=NULL)
                  follow->next=NULL;
              else
                  head=NULL;
              c=0;
          }
      }
      printTitle();
      if(follow!=NULL)
          printTable(head);
  }
  printf("\n\n\n");
}
TRAIN *search_list(TRAIN *list,int n)
{
 TRAIN *p;
 for (p = list; p != NULL; p = p->next)
 {
     if (p->num == n)
         return p;
 }
 return NULL;
}
void search()//Search for certain train by its number
{
    printf("\n\n\n");
    printf("---Please enter the train number---\n");
    int c;
    scanf("%d",&c);
    TRAIN *p;
    p=search_list(head,c);
    if(p==NULL)
    {
        printf("\n\n\n");
        printf("Train %d cannot be found\n",c);
    }
    else if(p!=NULL)
    {
        printTitle();
        printf("%12d\t%11s\t%10d:%d\t%9d:%d\n",p->num,p->dest,p->depart.hr,p->depart.min,p->arrive.hr,p->arrive.min);
    }
    printf("\n\n\n");
}
void insert()
{
   printf("\n\n\n");
   printf("---Please enter the train information you want to insert---");
   printf("\nTrain number: ");
   int tn;
   scanf("%d",&tn);
   printf("Destination: ");
   char d[20];
   scanf("%s",d);
   printf("Departure time: ");
   int dth,dtm;
   scanf("%d:%d",&dth,&dtm);
   printf("Arrival time: ");
   int ath,atm;
   scanf("%d:%d",&ath,&atm);
   TRAIN *new_train;
   new_train=newtrain(tn,d,dth,dtm,ath,atm);
   TRAIN *cur=head;
   TRAIN *p=head->next;
   int flag=1;
   int test=0;
   while(p!=NULL&&flag)
   {
       if(p->depart.hr>new_train->depart.hr)
       {
           flag=1;
           test++;
           cur=p;
           p=p->next;
       }
       else if(p->depart.hr==new_train->depart.hr)
       {
           if(p->depart.min>new_train->depart.min)
           {
               flag=1;
               test++;
               cur=p;
               p=p->next;
           }
           else
               flag=0;
       }
       else
           flag=0;
   }
   printf("\n\n\n");
   TRAIN *last=head->next;
   if(test==0||last==NULL)
   {
       printTitle();
       new_train->next=head;
       head=new_train;
       printTable(head);
       printf("\n\n\n");
   }
   else if(last!=NULL&&test)
   {
       new_train->next=p;
       cur->next=new_train;
       printTitle();
       printTable(head);
       printf("\n\n\n");

   }
}
TRAIN *delete_from_list(TRAIN *list,int n)
{
 TRAIN *cur, *prev;
 for (cur = list, prev = NULL;cur != NULL && cur->num != n;prev = cur, cur = cur->next);
 if (cur == NULL)
 {
     mark=0;
     return list; /* n was not found */
 }
 mark=1;
 if (prev == NULL)
    list = list->next; /* n is in the first node */
 else
    prev->next = cur->next; /* n is in some other node*/
 free(cur);
 return list;
}
void del()
{
    printf("\n\n\n");
    printf("---Please enter the train number you want to delete---\n");
    int c;
    scanf("%d",&c);
    TRAIN *p;
    head=p=delete_from_list(head,c);
    if(mark==0)
        printf("Train %d is not in the schedule\n",c);
    else if(mark)
    {
        printTitle();
        printTable(p);
        printf("\n\n\n");
    }
    else
    printf("There is no train available for departure currently \n");
}
void printTable(TRAIN *list)
{
    TRAIN *p=list;
    if(p !=NULL)
    {
        printTable(p->next);
        printf("%12d\t%11s\t%11d:%2d\t%9d:%2d\n",p->num,p->dest,p->depart.hr,p->depart.min,p->arrive.hr,p->arrive.min);
    }
}
