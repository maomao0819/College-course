#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <vector>
using namespace std;

void swap(int &a, int &b);
int* build_Array(ifstream& in_s, int& num_in_matrix, int& row, int& col);
int** build_Matrix(int row, int col, int arr[], int n);
void move_Upper_Left(int** matrix, int r, int c);
void move_Lower_Right(int** matrix, int row, int col, int r, int c);
void Insert(int** matrix, int row, int col, int value);
void Delete(int** matrix, int row, int col);
void print_Matrix(int ** matrix, int row, int col, ofstream& stream, int end_check);

static int max_num = INT_MAX;

int main()
{
    int num_case = 0;
    ifstream in_s;
    in_s.open("input.txt");
    ofstream out_s;
    out_s.open("output.txt");
    string str_case_num;
    getline(in_s, str_case_num);
    num_case = atoi(str_case_num.c_str());
    stringstream ss;
    string token;
    while (num_case--)
    {
        int row = 0, col = 0, op = 0;
        string str_op;
        getline(in_s, str_op);
        op = atoi(str_op.c_str());
        int num_in_matrix = 0;
        int *arr = 0;
        int **Young_Tableaus = 0;
        if (op == 1)
        {
            cout << "Insert ";
            out_s << "Insert ";
            string Insert_str;
            getline(in_s, Insert_str);
            vector <int> ins_arr;
            ss << Insert_str;
            while (ss >> token)
                ins_arr.push_back(atoi(token.c_str()));
            ss.clear();
            arr = build_Array(in_s, num_in_matrix, row, col);
            Young_Tableaus = build_Matrix(row, col, arr, num_in_matrix);
            vector<int>::iterator it_i;
            for (it_i = ins_arr.begin(); it_i != ins_arr.end(); it_i++)
            {
                cout << *it_i;
                out_s << *it_i;
                Insert(Young_Tableaus, row, col, *it_i);
                if (it_i + 1 != ins_arr.end())
                {
                    cout << " ";
                    out_s << " ";
                }
            }
            cout << "\n";
            out_s << "\n";
        }
        else if (op == 2)
        {
            cout << "Extract-min ";
            out_s << "Extract-min ";
            arr = build_Array(in_s, num_in_matrix, row, col);
            Young_Tableaus = build_Matrix(row, col, arr, num_in_matrix);
            int min_matrix = Young_Tableaus[0][0];
            cout << min_matrix << "\n";
            out_s << min_matrix << "\n";
            Delete(Young_Tableaus, row, col);
        }
        print_Matrix(Young_Tableaus, row, col, out_s, num_case);
        ss.clear();
    }
    in_s.close();
    out_s.close();
    return 0;
}

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int* build_Array(ifstream& in_s, int& num_in_matrix, int& row, int& col)
{
    vector <int> int_vec;
    string data;
    bool check = false;
    stringstream ss;
    string token;
    string temp;
    int tmp;
    do
    {
        getline(in_s, data);
        check = false;
        ss << data;
        while (ss >> token)
        {
            temp = token.c_str();
            if (temp == "x")
                int_vec.push_back(max_num);
            else
            {
                istringstream iss(temp);
                iss >> tmp;
                int_vec.push_back(tmp);
            }
            check = true;
        }
        ss.clear();
        row++;
    }
    while (check);
    row--;
    num_in_matrix = int_vec.size();
    col = num_in_matrix / row;
    int* int_arr = (int*)malloc(num_in_matrix * sizeof(int));
    vector<int>::iterator it_i;
    int* arr_id = int_arr;
    for (it_i = int_vec.begin(); it_i != int_vec.end(); it_i++)
        *arr_id++ = *it_i;
    return int_arr;
}

int** build_Matrix(int row, int col, int arr[], int n)
{
    int index = 0;
    int** matrix = (int **)malloc(row * sizeof(int*));
    for (int i = 0; i < row; i++)
    {
        matrix[i] = (int*)malloc(col * sizeof(int));
        for (int j = 0; j < col; j++)
        {
            if (index < n)
            {
                matrix[i][j] = arr[index];
                index++;
            }
        }
    }
    return matrix;
}

void move_Upper_Left(int **matrix, int r, int c)
{
    if(r == 0 && c == 0)
        return;
    int Row = r, Col = c;
    int UP = matrix[r][c], LEFT = matrix[r][c];
    if(r >= 1)
        UP = matrix[r - 1][c];
    if(c >= 1)
        LEFT = matrix[r][c - 1];
    if (matrix[r][c] < UP && UP >= LEFT)
    {
        Row = r - 1;
        Col = c;
    }
    else if (matrix[r][c] < LEFT && LEFT >= UP)
    {
        Row = r;
        Col = c - 1;
    }
    else
        return;
    swap(matrix[Row][Col], matrix[r][c]);
    move_Upper_Left(matrix, Row, Col);
}

void move_Lower_Right(int** matrix, int row, int col, int r, int c)
{
	if(r == row - 1 && c == col - 1)
        return;
	int Row = r;
	int Col = c;
	int DOWN = matrix[r][c], RIGHT = matrix[r][c];
    if(r < row - 1)
        DOWN = matrix[r + 1][c];
    if(c < col - 1)
        RIGHT = matrix[r][c + 1];
	if (matrix[r][c] > DOWN && DOWN <= RIGHT)
    {
		Row = r + 1;
		Col = c;
	}
	else if (matrix[r][c] > RIGHT && RIGHT <= DOWN)
	{
		Row = r;
		Col = c + 1;
	}
	else
        return;
    swap(matrix[Row][Col], matrix[r][c]);
    move_Lower_Right(matrix, row, col, Row, Col);
}

void Insert(int** matrix, int row, int col, int value)
{
	int R = row - 1, C = col - 1;
	if (matrix[R][C] != max_num)
		return;
	matrix[R][C] = value;
	move_Upper_Left(matrix, R, C);
}


void Delete(int** matrix, int row, int col)
{
	if (matrix[0][0] == max_num)
        return;
	matrix[0][0] = max_num;
	move_Lower_Right(matrix, row, col, 0, 0);
}

void print_Matrix(int** matrix, int row, int col, ofstream& stream, int end_check)
{
	for (int i = 0; i < row; i++)
    {
		for (int j = 0; j < col; j++)
        {
			if (matrix[i][j] == max_num)
            {
                cout << "x";
                stream << "x";
            }
			else
            {
                cout << matrix[i][j];
                stream << matrix[i][j];
            }
            if (j < col - 1)
            {
                cout << " ";
                stream << " ";
            }
		}
		cout << "\n";
		stream << "\n";
	}
	if (end_check)
    {
        cout << "\n";
        stream << "\n";
    }
}
