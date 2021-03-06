//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HW3_MagicSquare.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;

// PROTOTYPE DECLARATION
// Odd Magic Square
void MagicSquareOdd(int n, int ** magic_square, int initial_position, int movement);
// Doubly Even Magic Square
void MagicSquareDoublyEven(int n, int ** magic_square);
// Singly Even Magic Square
void siamese(int from, int to, int n, int ** magic_square);
void MagicSquareSinglyEven(int n, int ** magic_square);
// Print Magic Square
void PrintMagicSquare(int n, int ** magic_square, bool check, int memo);
// Delete Magic Square
void DeleteMagicSquare(int n, int ** magic_square);
// clear memo at which memo according argument
void ClearMemo(int memo);

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

// main
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	int n = StrToInt(Edit1->Text);
	// matrix declaration
	int ** magic_square;
	magic_square = new int * [n];
	// matrix initialization
	for (int i = 0; i < n; i++)
		magic_square[i] = new int [n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			magic_square[i][j] = 0;
	// initial position
	int initial_position = 0;
	int mark_initial_position = 0;
	if (RadioButton_top->Checked)
	{
		initial_position = 1;
		mark_initial_position++;
	}
	if (RadioButton_left->Checked)
	{
		initial_position = 2;
		mark_initial_position++;
	}
	if (RadioButton_bottom->Checked)
	{
		initial_position = 3;
		mark_initial_position++;
	}
	if (RadioButton_right->Checked)
	{
		initial_position = 4;
		mark_initial_position++;
	}
	// movement
	int movement = 0;
	int mark_movement = 0;
	if (CheckBox_LT->Checked)
	{
		movement = 1;
		mark_movement++;
	}
	if (CheckBox_LB->Checked)
	{
		movement = 2;
		mark_movement++;
	}
	if (CheckBox_RT->Checked)
	{
		movement = 3;
		mark_movement++;
	}
	if (CheckBox_RB->Checked)
	{
		movement = 4;
		mark_movement++;
	}
    int memo = 1;
	// check rightness of Magic Square
	bool check = CheckBox1->Checked;
	// Magic Square
	if (n % 2 == 1 && mark_initial_position != 1)
	{
		Form1->Memo1->Lines->Add("The number of initial position should be ONE!!");
		Form1->Memo1->Lines->Add("\n");
	}
	if (n % 2 == 1 && mark_movement != 1)
    {
		Form1->Memo1->Lines->Add("The number of movement should be ONE!!");
        Form1->Memo1->Lines->Add("\n");
	}
	else if (n % 2 == 0 || (n % 2 == 1 && mark_initial_position == 1 && mark_movement == 1))
	{
		// 1 * 1 Magic Square
		if (n == 1)
			magic_square[0][0] = 1;
		// Odd Magic Square
		else if (n % 2 == 1)
			MagicSquareOdd(n, magic_square, initial_position, movement);
		// Doubly Even Magic Square
		else if (n % 4 == 0)
			MagicSquareDoublyEven(n, magic_square);
		// Singly Even Magic Square
		else if (n % 2 == 0 && n > 2)
			MagicSquareSinglyEven(n, magic_square);
		// Print Magic Square
		if (n != 2)
			PrintMagicSquare(n, magic_square, check, memo);
	}
	memo = 2;
	if (n % 2 == 1)
	{
		ClearMemo(memo);
		for (int i = 1; i <= 4; i++)
		{
			for (int j = 1; j <= 4; j++)
			{
				MagicSquareOdd(n, magic_square, i, j);
				PrintMagicSquare(n, magic_square, check, memo);
			}
		}
    }
	// matrix delete
	DeleteMagicSquare(n, magic_square);
}
//---------------------------------------------------------------------------

// FUNCTION DEFINITION
// Odd Magic Square
void MagicSquareOdd(int n, int ** magic_square, int initial_position, int movement)
{
	// error n
	if (n == 2)
	{
		Form1->Memo1->Lines->Add("???J??????????????2?A?????B?z");
		return;
	}
	// matrix initialization
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			magic_square[i][j] = 0;
	int i, j;
	// initial position
	switch (initial_position)
	{
		case 1:
			i = 0;
			j = (n - 1) / 2;
			break;
		case 2:
			i = (n - 1) / 2;
			j = 0;
			break;
		case 3:
			i = (n - 1);
			j = (n - 1) / 2;
			break;
		case 4:
			i = (n - 1) / 2;
			j = n - 1;
	}
	// movement
	int move_x, move_y;
	switch (movement)
	{
		case 1:
			move_x = -1;
			move_y = -1;
			break;
		case 2:
			move_x = -1;
			move_y = 1;
			break;
		case 3:
			move_x = 1;
			move_y = -1;
			break;
		case 4:
			move_x = 1;
			move_y = 1;
	}
	int steps;
	magic_square[i][j] = 1;
	// fill data into matrix
	steps = 2;
	while (steps <= n * n)
	{
		// move
		i += move_y;
        if (i < 0)
			i += n;
		j += move_x;
		if (j < 0)
			j += n;
        i %= n;
		j %= n;
		// already exist value
		if (magic_square[i][j] > 0)
		{
			i = (i - 2 * move_y);
			if (i < 0)
				i += n;
			j = (j - 1 * move_x);
			if (j < 0)
				j += n;
            i %= n;
			j %= n;
		}
		// fill data
		magic_square[i][j] = steps++;
	}
}

// Function for calculating Doubly Even Magic square
void MagicSquareDoublyEven(int n, int ** magic_square)
{
	// filling matrix with its count value starting from 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			magic_square[i][j] = (n * i) + j + 1;

	// change value of Array elements at fix location as per rule (n * n + 1) - arr[i][j]
	// Left Top corner of Matrix (order (n / 4) * (n / 4))
	for (int i = 0; i < n / 4; i++)
		for (int j = 0; j < n / 4; j++)
			magic_square[i][j] = (n * n + 1) - magic_square[i][j];

	// Right Top corner of Matrix (order (n / 4) * (n / 4))
	for (int i = 0; i < n / 4; i++)
		for (int j = 3 * (n / 4); j < n; j++)
			magic_square[i][j] = (n * n + 1) - magic_square[i][j];

	 // Left Bottom corner of Matrix (order (n / 4) * (n / 4))
	for (int i = 3 * n / 4; i < n; i++)
		for (int j = 0; j < n / 4; j++)
			magic_square[i][j] = (n * n + 1) - magic_square[i][j];

	// Right Bottom corner of Matrix (order (n / 4) * (n / 4))
	for (int i = 3 * n / 4; i < n; i++)
		for (int j = 3 * n / 4; j < n; j++)
			magic_square[i][j] = (n * n + 1) - magic_square[i][j];

	// Centre of Matrix (order (n / 2) * (n / 2))
	for (int i = n / 4; i < 3 * n / 4; i++)
		for (int j = n / 4; j < 3 * n / 4; j++)
			magic_square[i][j] = (n * n + 1) - magic_square[i][j];
}

void siamese(int from, int to, int n, int ** magic_square)
{
	int oneSide = to - from;
	int col = oneSide / 2;
	int row = 0;
	int count = oneSide * oneSide;
	int s = 1;
	while (count > 0)
	{
		bool done = false;
		while (done == false)
		{
			if(col >= oneSide)
				col = 0;
			if(row < 0)
				row = oneSide - 1;
			done = true;
			if (magic_square[row][col] != 0)
			{
				col -= 1;
				row += 2;
				if(col < 0)
					col = oneSide - 1;
				if(row >= oneSide)
					row -= oneSide;
				done = false;
			}
		}
		magic_square[row][col] = s;
		s++;
		count--;
		col++;
		row--;
	}
}

// Function for calculating Singly Even Magic square
void MagicSquareSinglyEven(int n, int ** magic_square)
{
	int half_n = n / 2;
	int add1 = n * n / 2;
	int add3 = n * n / 4;
	int add2 = 3 * add3;
	siamese(0, half_n, n, magic_square);

	for( int r = 0; r < half_n; r++ )
	{
		int i = 0;
		int j = 0;
		int row = r * n;
		for (int c = half_n; c < n; c++)
		{
			int m = magic_square[r][c - half_n];
			magic_square[r][c] = m + add1;
			magic_square[r + half_n][c] = m + add3;
			magic_square[r + half_n][c - half_n] = m + add2;
		}
	}

    int lc = (n - 2) / 4, co = n - (lc - 1);
    for (int r = 0; r < half_n; r++)
	{
        for (int c = co; c < n; c++)
		{
			magic_square[r][c] -= add3;
			magic_square[r + half_n][c] += add3;
        }
	}

    for (int r = 0; r < half_n; r++)
    {
        for (int c = 0; c < lc; c++ )
        {
            int cc = c;
			if (r == lc)
				cc++;
			magic_square[r][cc] += add2;
			magic_square[r + half_n][cc] -= add2;
        }
	}
}

// Print Magic Square
void PrintMagicSquare(int n, int ** magic_square, bool check, int memo)
{
	if (memo == 1)
		Form1->Memo1->Lines->Add("----- " + IntToStr(n) + " ?? " + IntToStr(n) + " ???]?N???? -----\n");
	else if (memo == 2)
		Form1->Memo2->Lines->Add("----- " + IntToStr(n) + " ?? " + IntToStr(n) + " ???]?N???? -----\n");
	int max_len = IntToStr(n * n).Length();
	int block_len = max_len + 5;
	int blank_len;
	// record sums of the rows of Magic Square
	int * row_sum;
	row_sum = new int [n];
	for (int i = 0; i < n; i++)
		row_sum[i] = 0;
	// print Magic Square at memo1
	for (int i = 0; i < n; i++)
	{
		String row;
		for (int j = 0; j < n; j++)
		{
			blank_len = block_len - IntToStr(magic_square[i][j]).Length();
			for (int k = 0; k < blank_len; k++)
				row += " ";
			row += IntToStr(magic_square[i][j]);
			if (check)
				row_sum[i] += magic_square[i][j];
		}
		if (check)
		{
			row += "  -->  ";
			row += IntToStr(row_sum[i]);
		}
		if (memo == 1)
			Form1->Memo1->Lines->Add(row);
		else if (memo == 2)
			Form1->Memo2->Lines->Add(row);
	}
	// record sums of the columns of Magic Square
	int * column_sum;
	column_sum = new int [n];
	for (int i = 0; i < n; i++)
		column_sum[i] = 0;
	// record sums of the diagonals of Magic Square
	int * diagonal_sum;
	diagonal_sum = new int [2];
	for (int i = 0; i < 2; i++)
		diagonal_sum[i] = 0;
	// print row sums, column sums, and diagonal sums
	if (check)
	{
		String other_sum = "";
		for (int i = 0; i < n; i++)
		{
            column_sum[i] = 0;
			for (int j = 0; j < n; j++)
				column_sum[i] += magic_square[j][i];
			blank_len = block_len - IntToStr(column_sum[i]).Length();
			for (int k = 0; k < blank_len - 1; k++)
				other_sum += " ";
			other_sum += "|";
			other_sum += IntToStr(column_sum[i]);
		}
		diagonal_sum[0] = 0;
		for (int i = 0; i < n; i++)
			diagonal_sum[0] += magic_square[i][i];
		blank_len = block_len - IntToStr(diagonal_sum[0]).Length();
		for (int j = 0; j < blank_len - 1; j++)
			other_sum += " ";
		other_sum += "\\";
		other_sum += IntToStr(diagonal_sum[0]);

		diagonal_sum[1] = 0;
		for (int i = 0; i < n; i++)
			diagonal_sum[1] += magic_square[n - i - 1][i];
		blank_len = block_len - IntToStr(diagonal_sum[1]).Length();
		for (int j = 0; j < blank_len - 1; j++)
			other_sum += " ";
		other_sum += "/";
		other_sum += IntToStr(diagonal_sum[1]);
		if (memo == 1)
			Form1->Memo1->Lines->Add(other_sum);
		else if (memo == 2)
			Form1->Memo2->Lines->Add(other_sum);
	}
	if (memo == 1)
		Form1->Memo1->Lines->Add("\n");
	else if (memo == 2)
		Form1->Memo2->Lines->Add("\n");
	// print Magic Square in StringGrid
	// print Magic Square, row sums, column sums, and diagonal sums in StringGrid
	if (check && memo == 1)
	{
		Form1->StringGrid1->RowCount = n + 1;
		Form1->StringGrid1->ColCount = n + 1;

        for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				Form1->StringGrid1->Cells[j][i] = magic_square[i][j];

		for (int i = 0; i < n + 1; i++)
		{
			if (i < n)
			{	
				for (int j = 0; j < n + 1; j++)
				{
					if (j < n)
						Form1->StringGrid1->Cells[j][i] = magic_square[i][j];
					else
						Form1->StringGrid1->Cells[j][i] = row_sum[i];
				}
			}
			else
				for (int j = 0; j < n; j++)
					Form1->StringGrid1->Cells[j][i] = column_sum[j];	
		}
		Form1->StringGrid1->Cells[n][n] = diagonal_sum[0];
	}
	// print Magic Square in StringGrid
	else if (memo == 1)
	{
		Form1->StringGrid1->RowCount = n;
		Form1->StringGrid1->ColCount = n;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				Form1->StringGrid1->Cells[j][i] = magic_square[i][j];
	}
	// check if it is magic square and print the result
	if (check)
	{
		int * line_sum;
		line_sum = new int [3];
		line_sum[0] = row_sum[0];
		line_sum[1] = column_sum[0];
		line_sum[2] = diagonal_sum[0];
		bool check_sum = true;
		// check with row sums
		for (int i = 0; i < n - 1; i++)
		{
			if (row_sum[i] != row_sum[i + 1])
			{
				check_sum = false;
				break;
			}
		}
		// check with column sums
		if (check_sum == true)
		for (int i = 0; i < n - 1; i++)
		{
			if (column_sum[i] != column_sum[i + 1])
			{
				check_sum = false;
				break;
			}
		}
		// check with diagonal sums
		if (check_sum == true)
		for (int i = 0; i < 2 - 1; i++)
		{
			if (diagonal_sum[i] != diagonal_sum[i + 1])
			{
				check_sum = false;
				break;
			}
		}
		// print the result of checking
		if (check_sum == true)
		{
			if (memo == 1)
				Form1->Memo1->Lines->Add("   It is THE Magic Square!!");
			else if (memo == 2)
				Form1->Memo2->Lines->Add("   It is THE Magic Square!!");
		}
		else
		{
			if (memo == 1)
				Form1->Memo1->Lines->Add("   It is NOT Magic Square!!");
			else if (memo == 2)
				Form1->Memo2->Lines->Add("   It is NOT Magic Square!!");
		}
	}
	if (memo == 1)
		Form1->Memo1->Lines->Add("\n");
	else if (memo == 2)
        Form1->Memo2->Lines->Add("\n");
	// free memory
	delete [] row_sum;
	delete [] column_sum;
	delete [] diagonal_sum;
}

// Delete Magic Square
void DeleteMagicSquare(int n, int ** magic_square)
{
	for (int i = 0; i < n; i++)
		delete [] magic_square[i];
	delete [] magic_square;
}

// clear memo at which memo according argument
void ClearMemo(int memo)
{
    switch(memo)
	{
		case 1:
			Form1->Memo1->Lines->Clear();
			break;
		case 2:
			Form1->Memo2->Lines->Clear();
	}
}
