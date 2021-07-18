#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;
#define maxnum 10000
#define prime 9973

class patient
{
	friend class HashTable;
	private:
		string gender;
		int id,height,weight;
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
 class HashTable: public patient
 {
 	friend class patient;
 	private:
 		patient hashtab[maxnum];
 	public:
 		hashtable()
 		{
 			int i;
 			for(int i=0;i<maxnum;i++)
 			{
 				hashtab[i].id=0;
 				hashtab[i].height=0;
 				hashtab[i].weight=0;
 				hashtab[i].gender="";
 			
			 }
		 }
		 int hashfun(int key)
		 {
		 	return (key%prime);
		 }
		 void addItem(string k,string g,int h,int w)
		 {
		 	patient node;
		 	int index,count=0;
		 	int temp=atoi(k.c_str());
		 	node.id=temp;
			node.gender=g;
			node.weight=w;
			node.height=h;
			index=hashfun(temp);
			if(hashtab[index].id==0)
			{
				hashtab[index].id=node.id;
				hashtab[index].gender=node.gender;
				hashtab[index].height=node.height;
				hashtab[index].weight=node.weight;
				
			}
			else
			{
				collision(node,index);
			}
			//cout<<node.gender<<" "<<node.height<<" "<<node.weight<<endl;
				
				
			
			
				
		} 
		void collision(patient node,int i)
		{
			int j;
			j=i;
			while(hashtab[j].id!=node.id&&hashtab[j].id!=0)
			{
				j=(j+1)%prime;
				if(j==i)
					return;
			}
			if(hashtab[j].id==0)
			{
				hashtab[j].id=node.id;
				hashtab[j].gender=node.gender;
				hashtab[j].height=node.height;
				hashtab[j].weight=node.weight;
			}
		}
		patient& operator[](string k)
		{
		
//			//patient &pt=(*ptp);
			int temp=atoi(k.c_str());
			int index=hashfun(temp);
			return hashtab[index];
		}
		
		
 };
 
