#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
using namespace std;

void swap(int &a, int &b);
int** build_Matrix(int row, int col, int arr[], int n);
void move_Upper_Left(int** matrix, int r, int c);
void move_Lower_Right(int** matrix, int row, int col, int r, int c);
void Insert(int** matrix, int row, int col, int value);
void Delete(int** matrix, int row, int col);
void print_Matrix(int ** matrix, int row, int col, ofstream& stream);

static int max_num = 99999999;
static int max_len_of_array = 10000;

int main()
{
    int num_case = 0;
    ifstream in_s;
    in_s.open("input.txt");
    ofstream out_s;
    out_s.open("output.txt");
    string str_case_num;
    getline(in_s, str_case_num);
    stringstream ss;
    ss << str_case_num;
    string token;
    while (ss >> token)
        num_case = atoi(str_case_num.c_str());
    ss.clear();
    while (num_case--)
    {
        int row = 0, col = 0, op = 0;
        string str_op;
        getline(in_s, str_op);
        ss << str_op;
        while (ss >> token)
            op = atoi(token.c_str());
        int matrix_num[max_len_of_array];
        string matrix_str[max_len_of_array];
        ss.clear();
        int lineArr[1000];
        int num_in_matrix = 0;
        bool check = false;
        string data;
        if (op == 1)
        {
            cout << "Insert ";
            out_s << "Insert ";
            string Insert_str;
            getline(in_s, Insert_str);
            int Insert_Arr[1000];
            int insert_num = 0;
            ss << Insert_str;
            while (ss >> token)
            {
                Insert_Arr[insert_num] = atoi(token.c_str());
                cout << Insert_Arr[insert_num] << " ";
                out_s << Insert_Arr[insert_num] << " ";
                insert_num++;
            }
            ss.clear();
            cout << "\n";
            out_s << "\n";
            do
            {
                getline(in_s, data);
                check = false;
                ss << data;
                while (ss >> token)
                {
                    matrix_str[num_in_matrix] = (token.c_str());
                    if (matrix_str[num_in_matrix] == "x")
                        matrix_num[num_in_matrix] = max_num;
                    else
                    {
                        istringstream iss(matrix_str[num_in_matrix]);
                        iss >> matrix_num[num_in_matrix];
                    }
                    num_in_matrix++;
                    check = true;
                }
                ss.clear();
                row++;
            }
            while (check);
            row--;
            col = num_in_matrix / row;
            int **Young_Tableaus = build_Matrix(row, col, matrix_num, num_in_matrix);
            for(int i = 0; i < insert_num; i++)
                Insert(Young_Tableaus, row, col, Insert_Arr[i]);
            print_Matrix(Young_Tableaus, row, col, out_s);
        }
        else if (op == 2)
        {
            cout << "Extract-min ";
            out_s << "Extract-min ";
            do
            {
                getline(in_s, data);
                check = false;
                ss << data;
                while (ss >> token)
                {
                    matrix_str[num_in_matrix] = (token.c_str());
                    if(matrix_str[num_in_matrix] == "x")
                        matrix_num[num_in_matrix] = max_num;
                    else
                    {
                        istringstream iss(matrix_str[num_in_matrix]);
                        iss >> matrix_num[num_in_matrix];
                    }
                    num_in_matrix++;
                    check = true;
                }
                ss.clear();
                row++;
            }
            while (check);
            row--;
            col = num_in_matrix / row;
            int **Young_Tableaus = build_Matrix(row, col, matrix_num, num_in_matrix);
            int min_matrix = Young_Tableaus[0][0];
            cout << min_matrix << "\n";
            out_s << min_matrix << "\n";
            Delete(Young_Tableaus, row, col);
            print_Matrix(Young_Tableaus, row, col, out_s);
        }
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
    int Row = r, Col = c;
    if ((r - 1) >= 0 && matrix[r-1][c] > matrix[r][c])
    {
        Row = r - 1;
        Col = c;
    }
    if ((c - 1) >=0 && matrix[r][c-1] > matrix[Row][Col])
    {
        Row = r;
        Col = c - 1;
    }
    if (Row != r || Col != c)
    {
        swap(matrix[Row][Col], matrix[r][c]);
        move_Upper_Left(matrix, Row, Col);
    }
}

void move_Lower_Right(int** matrix, int row, int col, int r, int c)
{
	int Row = r, Col = c;
	if ((r + 1) < row && matrix[r + 1][c] < matrix[r][c])
    {
		Row = r + 1;
		Col = c;
	}
	if ((c + 1) < col && matrix[r][c + 1] < matrix[Row][Col])
	{
		Row = r;
		Col = c + 1;
	}
	if (Row != r || Col != c)
	{
		swap(matrix[Row][Col], matrix[r][c]);
		move_Lower_Right(matrix, row, col, Row, Col);
	}
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
	matrix[0][0] = max_num;
	move_Lower_Right(matrix, row, col, 0, 0);
}

void print_Matrix(int** matrix, int row, int col, ofstream& stream)
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
            if(j < col - 1)
            {
                cout << " ";
                stream << " ";
            }

		}
		cout << "\n";
		stream << "\n";
	}
	cout << "\n";
    stream << "\n";
}
