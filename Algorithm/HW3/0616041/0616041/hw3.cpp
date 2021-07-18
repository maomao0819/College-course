#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;
int line=0;
int main(){
    ifstream  in;
    ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int DP[100];
    int data = 0;
    int x = 0,y = 0, n = 0, temp=0, nil=1;

    string str1;          
    int DP1[100];
    int temp1=0;
    string str4;
    getline(in,str1);
    stringstream ss(str1);
    while(ss >> str4){
        DP1[temp1] = atoi(str4.c_str());
        temp1++;
    }
    do{

        for(int i=0;i<temp1;i++){
          DP[i] = DP1[i];
        }
        y = 0;
        if(line==0){
            data = temp1;
        }
        else if(line==1){
            data = temp;
        }


        do{
            n = 0;
            string str2;
            getline(in,str2);
            stringstream s1(str2);
            while(s1 >> str4){
                DP[data] = atoi(str4.c_str());
                data++;
                n++;
            }
            y++;
        }while(n>0);
        x = (data/y);
        int table[100][100];
        int tabledata = 0;
        for(int i=0;i<100;i++){
            for(int j=0;j<100;j++){
                table[i][j] = 0;
            }
        }

        for(int i=0;i<y;i++){
            for(int j=0;j<x;j++){
                table[i][j] = DP[tabledata];
                tabledata++;
            }
        }
        int temp1 = x;
        x = y;
        y = temp1;
        int temptable[100][100];
        for(int i=0;i<100;i++){
            for(int j=0;j<100;j++){
                temptable[i][j] = table[j][i];
            }
        }
        for(int i=0;i<100;i++){
            for(int j=0;j<100;j++){
                table[i][j] = temptable[i][j];
            }
        }

        int check = 0;
        do{
            nil = 0;
            int DAYS=0;
            check=0;
            string str1;
            getline(in,str1);
            stringstream ss1(str1);
            while(ss1 >> str4){
                DP1[check] = atoi(str4.c_str());
                check++;
                nil++;
            }
            if(check>1){
                line = 1;
                temp = check;
            }
            else if(check==1){
                string none;
                getline(in,none);
                DAYS = DP1[0];

		
                int finalTable[y+1][DAYS+1];
                for(int i=0;i<y+1;i++){
                    for(int j=0;j<DAYS+1;j++){
                        finalTable[i][j] = 0;
                    }
                }
                for(int i=0;i<x;i++){
                    finalTable[0][i] = table[0][i];
                }
                for(int i=1;i<y;i++){
                    int j=i;
                    for(int l=0;l<x;l++){
                        for(int k=(j+l)-1;k>=0;k--){
                            if(finalTable[i-1][k]+table[i][(i+l)-k-1] > finalTable[i][j+l]){
                                finalTable[i][j+l] = finalTable[i-1][k]+table[i][j+l-k-1];
                            	}
                        	}
						}
                	}
                int answer=finalTable[y-1][DAYS-1];
                cout << answer << endl;
                out << answer << endl;
            }
		}while(check==1);
    }while(nil!=0);
    in.close();
    out.close();
}
