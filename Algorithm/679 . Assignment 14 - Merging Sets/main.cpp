#include <iostream>
#include <set>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
int main(int argc, char** argv) {
	int depth,size;
	cin>>depth>>size;
	multiset<int> myset;
	int *count=new int[size];
	for(int i=0;i<size;i++){
		cin>>count[i];
		myset.insert(count[i]);
	}
	 multiset<int>::iterator it;
    while(size>1){
        int c=*--myset.end();
        it=myset.end();
        it--;
        myset.erase(it--);
        myset.erase(it--);
        myset.insert(c - depth);
        size--;
    }
    int c=*--myset.end();
    cout<<c<<endl;
	return 0;
}
