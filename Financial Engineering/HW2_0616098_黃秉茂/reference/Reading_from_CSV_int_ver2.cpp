#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
using namespace std;
int main()
{
  vector<double> matrix;
  //readfile
  fstream file;
  file.open("a.csv");
  string line;
  while (getline( file, line,'\n'))  //讀檔讀到跳行字元
	{
	  istringstream templine(line); // string 轉換成 stream
	  string data;
	  while (getline( templine, data,',')) //讀檔讀到逗號
	  {
	    matrix.push_back(atof(data.c_str()));  //string 轉換成數字
	  }
	}
  file.close();

  //writefile
  file.open("write.csv");
  for (int i=0;i<matrix.size();i++)
  {
    file << matrix[i]<<",";
    cout << matrix[i]<<",";
  }
  file.close();
  return 0;
}
