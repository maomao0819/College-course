#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
using namespace std;
void printMatrix(int ** matrix, int x, int y) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (987654 == matrix[i][j]) {
				cout << "x" << ends;
			} else {
				cout << matrix[i][j] << ends;
			}
		}
		cout << endl;
	}
}
void swap(int &a,int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
int** build(int x, int y,int arr[],int n){
    int k=0;
    int** matrix=(int **)malloc(x*sizeof(int*));
        for(int i=0;i<x;i++){
            matrix[i] = (int*)malloc(y*sizeof(int));
            for(int j=0;j<y;j++){
                if(k<n){
                    matrix[i][j] = arr[k];
                    k++;
                }
            }
        }
        return matrix;
}
void moveUp(int **matrix, int r, int c)
{
    int Row, Col;
    if((r-1)>=0 && matrix[r-1][c]>matrix[r][c]){
        Row = r-1;
        Col = c;
    }
    else{
        Row = r;
        Col = c;
    }
    if((c-1)>=0 && matrix[r][c-1]>matrix[Row][Col]){
        Row = r;
        Col = c - 1;
    }
    if(Row != r || Col != c){
        swap(matrix[Row][Col],matrix[r][c]);
        moveUp(matrix,Row,Col);
    }
}

void moveDown(int** matrix, int x, int y, int r, int c) {
	int Row, Col;
	if ((r + 1) < x && matrix[r + 1][c] < matrix[r][c]) {
		Row = r + 1;
		Col = c;
	} else {
		Row = r;
		Col = c;
	}
	if ((c + 1) < y && matrix[r][c + 1] < matrix[Row][Col]) {
		Row = r;
		Col = c + 1;
	}
	if (Row != r || Col != c) {
		swap(matrix[Row][Col], matrix[r][c]);
		moveDown(matrix, x, y, Row, Col);
	}
}
void Insert(int** matrix, int x, int y, int value) {
	if (987654 != matrix[x - 1][y - 1])
		return;
	matrix[x - 1][y - 1] = value;
	moveUp(matrix, x - 1, y - 1);
}


void Delete(int** matrix, int x, int y) {
	int r=0, c=0;
	matrix[0][0]=987654;
	moveDown(matrix, x, y, r, c);
}
int main()
{
    int n1=0;
    ifstream in;
    in.open("input.txt");
    ofstream out;
    out.open("output.txt");
    string str1;
    getline(in,str1);
    stringstream ss(str1);
    string token;
    while(ss >> token){
        n1= atoi(str1.c_str());
    }

    for(;n1>0;n1--){
        int y=0,x=-1,p=0;
        string str;
        getline(in,str);
        stringstream ss1(str);
        while(ss1 >> token){
            p = atoi(token.c_str());
        }
        int arr1[10000];
        string arr2[10000];
        int lineArr[100];
        int n=0;
        int e=0;
        if(p==1){
            out << "Insert ";
            cout << "Insert ";
            string Insert1;
            getline(in,Insert1);
            int insertArr[100];
            int d=0;
            stringstream ss(Insert1);
            while(ss >> token){
                insertArr[d] = atoi(token.c_str());

                out << insertArr[d] << " ";
                d++;
            }
            for(int i=0;i<d;i++){
                cout << insertArr[i] << endl;
            }
            cout << endl;
            out << endl;

            do{
                string data;
                getline(in,data);
                e=0;
                stringstream ss2(data);
                while(ss2 >> token){
                    arr2[n] = (token.c_str());
                    if(arr2[n]=="x"){
                        arr1[n] = 987654;
                    }
                    else{
                        istringstream is(arr2[n]);
                        is >> arr1[n];
                    }
                    n++;
                    e++;
                }
                x++;

            }while(e>0);
            y = n/x;

            int **matrix = build(x,y,arr1,n);
            for(int i=0;i<d;i++){
                Insert(matrix,x,y,insertArr[i]);
            }
            printMatrix(matrix,x,y);
            for(int i=0;i<x;i++){
                for(int j=0;j<y;j++){
                    if(matrix[i][j]==987654)
                        out << "x" << " ";
                    else
                        out << matrix[i][j] << " ";
                }
                out << endl;
            }
            out << endl;
            cout << endl;



        }

        else if(p==2){
                out << "Extract-min ";
                cout << "Extract-min ";
                do{
                string data;
                getline(in,data);
                e=0;
                stringstream ss2(data);
                while(ss2 >> token){
                    arr2[n] = (token.c_str());
                    if(arr2[n]=="x"){
                        arr1[n] = 987654;
                    }
                    else{
                        istringstream is(arr2[n]);
                        is >> arr1[n];
                    }
                    n++;
                    e++;
                }
                x++;

            }while(e>0);

            y = n/x;
            int **matrix = build(x,y,arr1,n);
            out << matrix[0][0] << endl;
            cout << matrix[0][0] << endl;
            Delete(matrix,x,y);
            printMatrix(matrix,x,y);

             for(int i=0;i<x;i++){
                for(int j=0;j<y;j++){
                    if(matrix[i][j]==987654)
                        out << "x" << " ";
                    else
                        out << matrix[i][j] << " ";
                }
                out << endl;
            }
            out << endl;
            cout << endl;

        }
    }
    in.close();
    out.close();
}
