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
  while (getline( file, line,'\n'))  //Ū��Ū�����r��
	{
	  istringstream templine(line); // string �ഫ�� stream
	  string data;
	  while (getline( templine, data,',')) //Ū��Ū��r��
	  {
	    matrix.push_back(atof(data.c_str()));  //string �ഫ���Ʀr
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
