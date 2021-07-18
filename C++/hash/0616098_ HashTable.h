#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string>
using namespace std;
#define maxnum 9999 
#define prime 9973

class patient
{
	friend class HashTable;
	private:
		string gender;
		int id,height,weight;
		patient *link;
	public:
		int getHeight() const
		{
			return height;
		}
		int getWeight() const
		{
			return weight;
		}
		string getGender() const
		{
			return gender;
		}
 };
 class HashTable
 {
 	friend class patient;
 	private:
 		patient *hashtab[maxnum];
 	public:
 		HashTable()
 		{
 			int i;
 			for(int i=0;i<maxnum;i++)
 			{
 				hashtab[i]=NULL;
			}
		 }
		 int hashfun(int key)
		 {
		 	return (key%prime);
		 }
		 void addItem(string key,string gender,int height,int weight)
		 {
		 	patient *newnode;
		 	newnode=new patient;
		 	newnode->link=NULL;
		 	int temp=atoi(key.c_str());
		 	newnode->id=temp;
			newnode->gender=gender;
			newnode->weight=weight;
			newnode->height=height;
			int index=hashfun(temp);
			if(hashtab[index]==NULL)
				hashtab[index]=newnode;			
			else
			{
				newnode->link=hashtab[index]->link;
				hashtab[index]->link=newnode;
			}
		} 
		
		patient *search(patient *linklist,patient *node)
		{
			patient *ptr=linklist;
			if(ptr==NULL)
				return NULL;
			while(ptr->link!=NULL&&ptr->id!=node->id)
				ptr=ptr->link;
			return  ptr;
		}
		patient& operator[](string k)
		{
			patient pt;
			int temp=atoi(k.c_str());
			int index=hashfun(temp);
			pt.id=hashtab[index]->id;
			pt.gender=hashtab[index]->gender;
			pt.height=hashtab[index]->height;
			pt.weight=hashtab[index]->weight;
			return *hashtab[index];
		}
 };
 
