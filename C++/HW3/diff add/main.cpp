#include <iostream>

#include "0616098_ Link_List.h"

using namespace std;

int main()
{
    Link_List<int> linkList1;
    // test default constructor
    Link_List<int> linkList2(linkList1);
    cout<<"linkList2 : " << linkList2<<endl;
    // test getSize()
    cout << "linkList2 Size: " << linkList2.getSize() << endl;


    // test copy constructor

    // test insert_node(value), delete_node(), operator<<, operator>>

    Link_List<int> linkList3;

	cout << "Enter a integer: ";
    cin >> linkList3;
	cout << "linkList3: "<< linkList3 << endl;
    Link_List<int> linkList6(linkList3);
    cout << "linkList6: " << linkList6 << endl;
    linkList3.insert_node(11);
    cout << "linkList3: " << linkList3 << endl;
    Link_List<int> linkList7(linkList3);
    cout << "linkList7: " << linkList7 << endl;
    linkList3.insert_node(12);
    cout << "linkList3: " << linkList3 << endl;
    Link_List<int> linkList9(linkList3);
    cout << "linkList9: " << linkList9 << endl;
    linkList3.insert_node(13);
    cout << "linkList3: " << linkList3 << endl;
    linkList3.insert_node(14);
    cout << "linkList3: " << linkList3 << endl;
    linkList3.insert_node(15);
    cout << "Insert Boolean: " << linkList3.insert_node(16) << endl;
    cout << "linkList3: " << linkList3 << endl;

    cout << "Delete Boolean: " << linkList3.delete_node() << endl;
    cout << "linkList3: " << linkList3 << endl;

    // test assignment operator, equality operator, insert_node(index, value), delete_node(index)
    Link_List<int> linkList4=linkList3;
    cout << "linkList4: " << linkList4 << endl;
    cout << "Insert Boolean: " << linkList4.insert_node(3, 17) << endl;
    cout << "linkList4: " << linkList4 << endl;

    cout << "Delete Boolean: " << linkList4.delete_node(4) << endl;
    cout << "Equality Boolean: " << (linkList4==linkList3) << endl;
    cout << "linkList4: " << linkList4 << endl;

     //test subscript operator []
    const Link_List<int> linkList5= linkList4;
    cout << "linkList4[1]: " << linkList4[1] << endl;
    cout << "linkList5[1]: " << linkList5[3] << endl;
    Link_List<int> linkList8(linkList4);
    cout << "linkList8: " << linkList8 << endl;

	return 0;
}
