#ifndef LINK_LIST
#define LINK_LIST

#include <iostream>
using namespace std;

template <typename T>
struct Int_Node
{
	T value;
	Int_Node<T> *pre, *next;
};

template <typename T>
class Link_List
{
	template <typename U>
	friend ostream &operator<<(ostream &s, const Link_List<U> &a)  	// print all integers in the list
	{
        if(a.size==0)
        {
            s<<"\0";
            return s;
        }
        else if(a.size==1)
        {
            s<<a.head->value;
            return s;
        }
       /* else if(a.size==2)
        {
            s<<a.head->value<<" ";
            s<<a.tail->value;
            return s;
        }*/
        Int_Node<T> *ptr=a.head;
        for(ptr;ptr!=a.tail;ptr=ptr->next)
        {
            s<<ptr->value<<" ";
        }
        s<<a.tail->value;
        return s;
	}
	template <typename U>
	friend istream &operator>>(istream &s, Link_List<U> &a)			// input a value at the back of the list, like insert_node(val);
	{
        Int_Node<T> *ptr=new Int_Node<T>;
        if(a.size==0)
        {
            a.head->pre=NULL;
            a.tail=a.head;
            a.current=a.head;
            a.size=1;
            return s>>a.head->value;
        }
        else if(a.size==1)
        {
            a.tail=ptr;
            a.tail->pre=a.head;
            a.tail->next=NULL;
            a.head->next=a.tail;
            a.current=a.head;
            a.size=2;
            return s>>a.tail->value;
        }
        a.tail->next=ptr;
        ptr->pre=a.tail;
        ptr->next=NULL;
        a.current=a.tail;
        a.tail=ptr;
        s>>a.tail->value;
        a.size++;
        return s;
	}

public:
	Link_List()										// default constructor
	{
	    head=new Int_Node<T>;
	    head->next=head;
	    head->pre=head;
	    tail=head;
	    current=head;
	    size=0;
	}
	Link_List(const Link_List &a)						// copy constructor
	{
	    this->head=a.head;
	    this->tail=a.tail;
	    Int_Node<T> *current1=this->head;
	    Int_Node<T> *current2=a.head;
	   while(current2!=tail)
        {
            current1->next=current2->next;
            current1->pre=current2->pre;
            current1=current1->next;
            current2=current2->next;
        }
        this->size=a.size;
	}
	~Link_List()
	{
        current=head->next;
        while(current!=tail)
        {
            delete head;
            head=current;
            current=current->next;
        }
        delete tail;
	}
	int getSize() const
	{
	    return size;
	}

	const Link_List &operator=(const Link_List &a)		// assignment operator
	{
	    this->head=a.head;
	    this->tail=a.tail;
	    Int_Node<T> *current1=this->head;
	    Int_Node<T> *current2=a.head;
	    while(current2!=tail)
        {
            current1->next=current2->next;
            current1->pre=current2->pre;
            current1=current1->next;
            current2=current2->next;
        }
        this->size=a.size;
        return *this;
	}
	bool operator==(const Link_List &right) const			// equality operator
	{
	    if(this->size!=right.size)
            return false;
	    Int_Node<T> *current1=this->head;
	    Int_Node<T> *current2=right.head;
	    while(current1!=this->tail)
        {
            if(current1->value!=current2->value)
                return false;
            current1=current1->next;
            current2=current2->next;
        }
        if(this->tail->value!=right.tail->value)
                return false;
        return true;
	}
	bool operator!=(const Link_List &right) const		// inequality operator
	{
		return !(*this == right);
	}

	T &operator[](int index)							// subscript operator for non-const objects
	{
        int count=0;
        current=head;
        while(count!=index)
        {
            current=current->next;
            count++;
        }
        return current->value;
	}
	T operator[](int index) const						// subscript operator for const objects
	{
        int count=0;
        Int_Node<T> *cur=head;
        while(count!=index)
        {
            cur=cur->next;
            count++;
        }
        return cur->value;
	}
	bool insert_node(T value)							// insert an integer at the back of link list
	{
        Int_Node<T> *newnode=new Int_Node<T>;
        newnode->value=value;
        if(size==0)
        {
            head=newnode;
            head->pre=NULL;
            head->next=NULL;
            tail=head;
            current=head;
            size++;
            return true;
        }
        else if(size==1)
        {
            head->next=newnode;
            tail=newnode;
            tail->pre=head;
            tail->next=NULL;
            head->pre=NULL;
            size++;
            return true;
        }
        else if(size==2)
        {
            newnode->next=NULL;
            newnode->pre=tail;
            Int_Node<T> *temp=tail;
            tail=newnode;
            head->next=temp;
            temp->next=tail;
            size++;
            return true;
        }
        size++;
        //cout<<"size="<<size<<"   head="<<head<<"   head->next="<<head->next<<"    tail="<<tail<<"    tail->pre="<<tail->pre<<"   newnode="<<newnode<<endl;
        tail->next=newnode;
        newnode->pre=tail;
        newnode->next=NULL;
        tail=newnode;
        return true;
	}
	bool delete_node()									// delete the last node
	{
        Int_Node<T> *temp=tail;
        tail=tail->pre;
        delete temp;
        tail->next=NULL;
        size--;
        return true;
	}
	bool insert_node(int index, T value)				// insert an integer after the i_th position
	{
        if(index==size)
        {
            insert_node(value);
            return true;
        }
        int count=0;
        current=head;
        while(count!=index)
        {
            current=current->next;
            count++;
        }
        Int_Node<T> *newnode=new Int_Node<T>;
        newnode->value=value;
        Int_Node<T> *temp=current->next;
        current->pre->next=newnode;
        newnode->pre=current->pre;
        current->pre=newnode;
        newnode->next=current;
        current->next=temp;
        temp->pre=current;
        size++;
        /*Int_Node<T> *ptr=head;
        for(ptr;ptr!=tail;ptr=ptr->next)
        {
            cout<<ptr<<"    ";
        }
        cout<<tail;*/
        return true;
	}
	bool delete_node(int index)						// delete the i_th node
	{
        if(index==size)
        {
            delete_node();
            return true;
        }
        else if(index==0)
        {
            current=head->next;
            delete head;
            current->pre=NULL;
            head=current;
            return true;
        }
        int count=0;
        current=head;
        while(count!=index)
        {
            current=current->next;
            count++;
        }
        Int_Node<T> *temp1=current->next;
        Int_Node<T> *temp2=current->pre;
        delete current;
        temp1->pre=temp2;
        temp2->next=temp1;
        current=temp2;
        size--;
        return true;
	}
private:
	int size;
	Int_Node<T> *current, *head, *tail;								// pointer to the first and the last element of Link_List
};
#endif // LINK_LIST
