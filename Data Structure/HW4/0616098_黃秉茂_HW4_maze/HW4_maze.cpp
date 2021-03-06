//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HW4_maze.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

// DEFINE MACRO
#define possible_direction 8
#define maze_length 100

// using global variable to pass value easily
// 2d-array to record the maze
int maze[maze_length][maze_length];
// check if the maze has been created
bool is_maze_create = false;
// the number of rows in maze
int row;
// the number of columns in maze
int col;
// the index represent the top of the stack
int top = -1;

// create struct to keep offset x and offset y
typedef struct offset
{
	int dx;
	int dy;
} OFFSET;
enum directions {N, NE, E, SE, S, SW, W, NW};
// create movement with 8 directions with struct;s array
OFFSET movement[possible_direction];
// create struct to keep position's information
typedef struct position
{
	int x;
	int y;
	directions dir;
} POSITION;
// create the stack to store POSITION
POSITION *stack;

// PROTOTYPE DECLARATION
// create and initialize the stack
void InitializeStack();
// initialize movement
void InitializeMovement();
// create and initialize the maze
void CreateMaze();
// mark maze's border
void MazeBorder();
// print message when the stack is full and illegal push
void StackFull();
// print message when the stack is empty and illegal pop
void StackEmpty();
// push to the stack
void push(POSITION data);
// pop from the stack
POSITION pop();
// initialize StringGrids with/without
void InitializeStringGrid(bool border);
// print the maze with/without border
void PrintMaze(bool border);
// generate 0/1 and assign to fill the maze
void MazeRandData();
// set extrance if need
void SetExtrance();
// set exit if need
void SetExit();
// load txt data to maze
void LoadMaze();
// save maze to txt data
void SaveMaze();
// refresh StringGrids with/without border
void RefreshStringGrid(bool border);
// delete and free stack's memory
void DeleteStack();
// find the tour to the exit with try and error
void path();
// Scanning effect with animation
void ScanAnimation();

// MAIN
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	if (is_maze_create == false)
		// create and initialize the maze
		CreateMaze();
	row = StrToInt(Edit1->Text);
	col = StrToInt(Edit2->Text);
	// generate 0/1 and assign to fill the maze
	MazeRandData();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	if (is_maze_create == false)
		// create and initialize the maze
		CreateMaze();
	// load txt data to maze
	LoadMaze();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
    // save maze to txt data
	SaveMaze();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	// find the tour to the exit with try and error
	path();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
	ScanAnimation();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid2DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State)
{
	// set brush color of the stringgrid's canvas
	StringGrid2->Canvas->Brush->Color = clWhite;
	// set font color of the stringgrid's canvas
	StringGrid2->Canvas->Font->Color = clBlue;
	// draw and fill the stringgrid's canvas
	StringGrid2->Canvas->FillRect(Rect);
	// get maze's all rows' and all columns' data from StringGrid2's Cells
	AnsiString text = StringGrid1->Cells[ACol][ARow];
	// put text in StringGrid and set the relative position of the text to the grid
	StringGrid2->Canvas->TextRect(Rect, Rect.Left + 6, Rect.Top + 8, text);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid3DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State)
{
	// get maze's all rows' and all columns' data from StringGrid2's Cells
	AnsiString text = StringGrid1->Cells[ACol][ARow];
	// case from string to int for switch
	int categogy = StrToInt(text);
	// 0: has not been passed  1: barrier  2: border  3: passed  4: passed and abandonned  5: extrance and exit  6: scanning effect animation
	switch (categogy)
	{
		case 0:
			StringGrid3->Canvas->Brush->Color = TColor RGB(200, 202, 144);
			break;
		case 1:
			StringGrid3->Canvas->Brush->Color = TColor RGB(196, 164, 123);
			break;
		case 2:
			StringGrid3->Canvas->Brush->Color = TColor RGB(199, 142, 142);
			break;
		case 3:
			StringGrid3->Canvas->Brush->Color = TColor RGB(154, 196, 150);
			break;
		case 4:
			StringGrid3->Canvas->Brush->Color = TColor RGB(104, 146, 100);
            break;
		case 5:
			StringGrid3->Canvas->Brush->Color = TColor RGB(81, 173, 207);
	}
	// draw and fill the stringgrid's canvas
	StringGrid3->Canvas->FillRect(Rect);
	// put text in StringGrid and set the relative position of the text to the grid
	StringGrid3->Canvas->TextRect(Rect, Rect.Left + 6, Rect.Top + 8, text);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid4DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State)
{
	// get maze's all rows' and all columns' data from StringGrid2's Cells
	AnsiString text = StringGrid1->Cells[ACol][ARow];
	// case from string to int for switch
	int categogy = StrToInt(text);
	// 0: has not been passed  1: barrier  2: border  3: passed  4: passed and abandonned  5: extrance and exit  6: scanning effect animation
	char symbol = ' ';
	switch (categogy)
	{
		case 0:
			StringGrid4->Canvas->Brush->Color = TColor RGB(200, 202, 144);
			break;
		case 1:
			StringGrid4->Canvas->Brush->Color = TColor RGB(196, 164, 123);
			break;
		case 2:
			StringGrid4->Canvas->Brush->Color = TColor RGB(199, 142, 142);
			break;
		case 3:
			StringGrid4->Canvas->Brush->Color = TColor RGB(154, 196, 150);
			symbol = '@';
			break;
		case 4:
			StringGrid4->Canvas->Brush->Color = TColor RGB(104, 146, 100);
			symbol = '*';
            break;
		case 5:
			StringGrid4->Canvas->Brush->Color = TColor RGB(81, 173, 207);
			break;
		case 6:
			StringGrid4->Canvas->Brush->Color = TColor RGB(50, 50, 50);
	}
	// draw and fill the stringgrid's canvas
	StringGrid4->Canvas->FillRect(Rect);
	// put text in StringGrid and set the relative position of the text to the grid
	StringGrid4->Canvas->TextRect(Rect, Rect.Left + 15, Rect.Top + 15, symbol);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid5DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State)
{
	// get maze's all rows' and all columns' data from StringGrid2's Cells
	AnsiString text = StringGrid1->Cells[ACol][ARow];
	// case from string to int for switch
	int categogy = StrToInt(text);
	// 0: has not been passed  1: barrier  2: border  3: passed  4: passed and abandonned  5: extrance and exit  6: scanning effect animation
	switch (categogy)
	{
		case 0:
			StringGrid5->Canvas->Brush->Color = TColor RGB(200, 202, 144);
			break;
		case 1:
			StringGrid5->Canvas->Brush->Color = TColor RGB(196, 164, 123);
			break;
		case 2:
			StringGrid5->Canvas->Brush->Color = TColor RGB(199, 142, 142);
			break;
		case 3:
			StringGrid5->Canvas->Brush->Color = TColor RGB(154, 196, 150);
			break;
		case 4:
			StringGrid5->Canvas->Brush->Color = TColor RGB(104, 146, 100);
            break;
		case 5:
			StringGrid5->Canvas->Brush->Color = TColor RGB(81, 173, 207);
			break;
		case 6:
			StringGrid5->Canvas->Brush->Color = TColor RGB(50, 50, 50);
	}
	// draw and fill the stringgrid's canvas
	StringGrid5->Canvas->FillRect(Rect);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid6DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State)
{
	// get maze's all rows' and all columns' data from StringGrid2's Cells
	AnsiString text = StringGrid1->Cells[ACol][ARow];
	// case from string to int for switch
	int categogy = StrToInt(text);
	// 0: has not been passed  1: barrier  2: border  3: passed  4: passed and abandonned  5: extrance and exit  6: scanning effect animation
	switch (categogy)
	{
		case 0:
			StringGrid6->Canvas->Brush->Color = TColor RGB(200, 202, 144);
			break;
		case 1:
			StringGrid6->Canvas->Brush->Color = TColor RGB(196, 164, 123);
			break;
		case 2:
			StringGrid6->Canvas->Brush->Color = TColor RGB(199, 142, 142);
			break;
		case 3:
			StringGrid6->Canvas->Brush->Color = TColor RGB(154, 196, 150);
			break;
		case 4:
			StringGrid6->Canvas->Brush->Color = TColor RGB(104, 146, 100);
			break;
		case 5:
			StringGrid6->Canvas->Brush->Color = TColor RGB(81, 173, 207);
            break;
		case 6:
			StringGrid6->Canvas->Brush->Color = TColor RGB(50, 50, 50);
	}
	// draw and fill the stringgrid's canvas
	StringGrid6->Canvas->FillRect(Rect);
}
//---------------------------------------------------------------------------

// FUNCTION DEFINITION
// create and initialize the stack
void InitializeStack()
{
	stack = new POSITION [row * col];
    top = -1;
}

// initialize Movement
void InitializeMovement()
{
	// N
	movement[0].dx = -1;
	movement[0].dy = 0;
	// NE
	movement[1].dx = -1;
	movement[1].dy = 1;
	// E
	movement[2].dx = 0;
	movement[2].dy = 1;
	// SE
	movement[3].dx = 1;
	movement[3].dy = 1;
	// S
	movement[4].dx = 1;
	movement[4].dy = 0;
	// SW
	movement[5].dx = 1;
	movement[5].dy = -1;
	// W
	movement[6].dx = 0;
	movement[6].dy = -1;
	// NW
	movement[7].dx = -1;
	movement[7].dy = -1;
}

// create and initialize the maze
void CreateMaze()
{
	// initialize all the data in maze to zeto
	for (int i = 0; i < maze_length; i++)
		for (int j = 0; j < maze_length; j++)
				maze[i][j] = 0;
	// create and initialize the stack
	InitializeMovement();
	is_maze_create = true;
}

// mark maze's border
void MazeBorder()
{
	for (int i = 0; i < row + 2; i++)
		for (int j = 0; j < col + 2; j++)
			if (i == 0 || j == 0 || i == row + 2 - 1 || j == col + 2 - 1)
				// 2: border
				maze[i][j] = 2;
}

// print message when the stack is full and illegal push
void StackFull()
{
	Form1->Memo1->Lines->Add("PUSH is ILLEGAL! Stack is full!");
}

// print message when the stack is empty and illegal pop
void StackEmpty()
{
	Form1->Memo1->Lines->Add("POP is ILLEGAL! Stack is empty!");
}

// push to the stack
void push (POSITION data)
{
	if (top == (row * col - 1))
		StackFull();
	else
		stack[++top] = data;
    return;
}

// pop from the stack
POSITION pop()
{
	if (top == -1)
		StackEmpty();
	else
		return stack[top--];
}

// initialize StringGrids with/without border
void InitializeStringGrid(bool border)
{
	if (border == false)
	{
		row -= 2;
		col -= 2;
	}
	// print out maze[][] in StringGrid1
	// set the numbers of rows and columns
	Form1->StringGrid1->RowCount = row + 2;
	Form1->StringGrid1->ColCount = col + 2;
	for (int i = 0; i < row + 2; i++)
	{
		for (int j = 0; j < col + 2; j++)
		{
			if (border == false)
				Form1->StringGrid1->Cells[j][i] = maze[i + 1][j + 1];
			else
				Form1->StringGrid1->Cells[j][i] = maze[i][j];
        }
	}
	// set the numbers of rows and columns
	Form1->StringGrid2->RowCount = row + 2;
	Form1->StringGrid2->ColCount = col + 2;
	int grid_size = Form1->Edit7->Text.ToInt();
	// avoid vertical splitter too bold
	Form1->StringGrid2->DefaultDrawing = false;
	// fixed display when scrolling if the window size isn't adequate
	Form1->StringGrid2->FixedCols = 0;
	Form1->StringGrid2->FixedRows = 0;
	// set rows' heights and columns' widths in the grids
	for (int i = 0; i < row + 2; i++)
		Form1->StringGrid2->RowHeights[i] = grid_size;
	for (int j = 0; j < col + 2; j++)
		Form1->StringGrid2->ColWidths[j] = grid_size;
	// refresh
	Form1->StringGrid2->Refresh();
	// set the numbers of rows and columns
	Form1->StringGrid3->RowCount = row + 2;
	Form1->StringGrid3->ColCount = col + 2;
	// avoid vertical splitter too bold
	Form1->StringGrid3->DefaultDrawing = false;
	// fixed display when scrolling if the window size isn't adequate
	Form1->StringGrid3->FixedCols = 0;
	Form1->StringGrid3->FixedRows = 0;
	// set rows' heights and columns' widths in the grids
	for (int i = 0; i < row + 2; i++)
		Form1->StringGrid3->RowHeights[i] = grid_size;
	for (int j = 0; j < col + 2; j++)
		Form1->StringGrid3->ColWidths[j] = grid_size;
	// refresh
	Form1->StringGrid3->Refresh();
    // set the numbers of rows and columns
	Form1->StringGrid4->RowCount = row + 2;
	Form1->StringGrid4->ColCount = col + 2;
	// avoid vertical splitter too bold
	Form1->StringGrid4->DefaultDrawing = false;
	// fixed display when scrolling if the window size isn't adequate
	Form1->StringGrid4->FixedCols = 0;
	Form1->StringGrid4->FixedRows = 0;
	// set rows' heights and columns' widths in the grids
	for (int i = 0; i < row + 2; i++)
		Form1->StringGrid4->RowHeights[i] = grid_size;
	for (int j = 0; j < col + 2; j++)
		Form1->StringGrid4->ColWidths[j] = grid_size;
	// refresh
	Form1->StringGrid4->Refresh();
	// set the numbers of rows and columns
	Form1->StringGrid5->RowCount = row + 2;
	Form1->StringGrid5->ColCount = col + 2;
	// avoid vertical splitter too bold
	Form1->StringGrid5->DefaultDrawing = false;
	// fixed display when scrolling if the window size isn't adequate
	Form1->StringGrid5->FixedCols = 0;
	Form1->StringGrid5->FixedRows = 0;
	// set rows' heights and columns' widths in the grids
	for (int i = 0; i < row + 2; i++)
		Form1->StringGrid5->RowHeights[i] = grid_size;
	for (int j = 0; j < col + 2; j++)
		Form1->StringGrid5->ColWidths[j] = grid_size;
	// refresh
	Form1->StringGrid5->Refresh();
	// set the numbers of rows and columns
	Form1->StringGrid6->RowCount = row + 2;
	Form1->StringGrid6->ColCount = col + 2;
	// avoid vertical splitter too bold
	Form1->StringGrid6->DefaultDrawing = false;
	// fixed display when scrolling if the window size isn't adequate
	Form1->StringGrid6->FixedCols = 0;
	Form1->StringGrid6->FixedRows = 0;
	// set the line width of grids
	Form1->StringGrid6->GridLineWidth = 0;
	// set rows' heights and columns' widths in the grids
	for (int i = 0; i < row + 2; i++)
		Form1->StringGrid6->RowHeights[i] = grid_size;
	for (int j = 0; j < col + 2; j++)
		Form1->StringGrid6->ColWidths[j] = grid_size;
	// refresh
	Form1->StringGrid6->Refresh();
	if (border == false)
	{
		row += 2;
		col += 2;
	}
}

// print the maze with/without border
void PrintMaze(bool border)
{
	String out;
	// print with border
	if (border)
	{
		for (int i = 0; i < row + 2; i++)
		{
			out = "";
			for (int j = 0; j < col + 2; j++)
				out += ("  " + IntToStr(maze[i][j]));
			Form1->Memo1->Lines->Add(out);
		}
	}
	// print without border
	else
	{
		for (int i = 1; i < row + 2 - 1; i++)
		{
			out = "";
			for (int j = 1; j < col + 2 - 1; j++)
				out += ("  " + IntToStr(maze[i][j]));
			Form1->Memo1->Lines->Add(out);
		}
	}
	// initialize StringGrids with/without border
	InitializeStringGrid(border);
}

// set extrance if need
void SetExtrance()
{
	if (Form1->CheckBox1->Checked)
	{
		int extrance_x = Form1->Edit3->Text.ToInt();
		int extrance_y = Form1->Edit4->Text.ToInt();
		maze[1][1] = 5;
		if (extrance_x > row - 1)
			ShowMessage("Extrance x shouldn't bigger than maze's height");
		else if (extrance_y > col - 1)
			ShowMessage("Extrance y shouldn't bigger than maze's width");
		else
		{
            maze[1][1] = 0;
			maze[extrance_x + 1][extrance_y + 1] = 5;
		}
	}
	else
		// extrance
		maze[1][1] = 5;
}

// set exit if need
void SetExit()
{
	if (Form1->CheckBox2->Checked)
	{
		int exit_x = Form1->Edit5->Text.ToInt();
		int exit_y = Form1->Edit6->Text.ToInt();
		maze[row][col] = 5;
		if (exit_x > row - 1)
			ShowMessage("Exit x shouldn't bigger than Height! \nWe will create the maze with default(0, 0) as the extrance.");
		else if (exit_y > col - 1)
			ShowMessage("Exit y shouldn't bigger than Width! \nWe will create the maze with default(Height, Width) as the exit.");
		else
		{
			maze[row][col] = 0;
			maze[exit_x + 1][exit_y + 1] = 5;
		}
	}
	else
		// exit
		maze[row][col] = 5;
}

// generate 0/1 and assign to fill the maze
void MazeRandData()
{
	Form1->Memo1->Lines->Add("0: has not been passed  1: barrier  2: border  3: passed  4: passed and abandonned  5: extrance or exit");
	Form1->Memo1->Lines->Add("(row, col) = (" + IntToStr(row) + ", " + IntToStr(col) + ")");
	// generate random number by time
	srand(time(NULL));
	for (int i = 1; i < row + 2 - 1; i++)
		for (int j = 1; j < col + 2 - 1; j++)
			maze[i][j] = rand() % 2;
	// mark maze's border
	MazeBorder();
	// extrance
	maze[1][1] = 5;
	// exit
	maze[row][col] = 5;
	// set extrance if need
	SetExtrance();
	// set exit if need
	SetExit();
	bool border = false;
	// print the maze without border
	PrintMaze(border);
}

// load txt data to maze
void LoadMaze()
{
	// Define fp as a pointer pointing to some file (with data type FILE) in hard desk
	FILE *fp;
	if (Form1->OpenDialog1->Execute())
	{
        // Use builder's string (AnsiString) to ease the conversion (into const char *)
		AnsiString infile;
		infile = Form1->OpenDialog1->FileName;
		// The return value of function c_str is const char *, casting AnsiString to const char * for the use of fopen
		fp = fopen(infile.c_str(), "r+");
		// Read in two integers, row & col
		fscanf(fp, "%d %d", &row, &col);
		MazeBorder();
		Form1->Memo1->Lines->Add("0: has not been passed  1: barrier  2: border  3: passed  4: passed and abandonned  5: extrance or exit");
		Form1->Memo1->Lines->Add("(row, col) = (" + IntToStr(row) + ", " + IntToStr(col) + ")");
		// Read in row * col 0/1/2's into the maze[][]
		for (int i = 1; i < row + 1; i++)
			for (int j = 1; j < col + 1; j++)
				fscanf(fp, "%d", &maze[i][j]);
		fclose(fp);
		// print the maze without border
		bool border = false;
		PrintMaze(border);
		// set extrance if need
		SetExtrance();
		// set exit if need
		SetExit();
	}
}

// save maze to txt data
void SaveMaze()
{
    // Check SaveDialog1 access the file successfully
	if (Form1->SaveDialog1->Execute())
	{
		// get the filename which open with SaveDialog1. After casing the filename to char format, opening the file with fopen
		AnsiString file_name = Form1->SaveDialog1->FileName;
		// "w": open the file for writing file
		FILE *fp = fopen(file_name.c_str(), "w");
		// use fprintf to write the elements in the maze to fp, and use putc to add '\n' to fp when change line is needed.
		if (fp)
		{
			fprintf(fp, "%d %d", row, col);
			putc('\n', fp);
			for (int i = 1 ; i < row + 2 - 1 ; i++)
			{
				for (int j = 1 ; j < col + 2 - 1 ; j++)
					fprintf(fp, "%d ", maze[i][j]);
				putc('\n', fp);
			}
			// close the file after wtiting
			fclose(fp);
		}
	}
}

// refresh StringGrids with/without border
void RefreshStringGrid(bool border)
{
	if (Form1->CheckBox4->Checked)
		Form1->DoubleBuffered = true;
	else
		Form1->DoubleBuffered = false;
	for (int i = 0; i < row + 2; i++)
		for (int j = 0; j < col + 2; j++)
			Form1->StringGrid1->Cells[j][i] = maze[i][j];
	// refresh
	Form1->StringGrid2->Refresh();
	Form1->StringGrid3->Refresh();
	Form1->StringGrid4->Refresh();
	Form1->StringGrid5->Refresh();
	Form1->StringGrid6->Refresh();
	// use sleep to wait for animation effect
	if (Form1->CheckBox3->Checked)
		Sleep(Form1->TrackBar1->Position);
}

// delete and free stack's memory
void DeleteStack()
{
	delete [] stack;
	return;
}

// find the tour to the exit with try and error
void path()
{
	// DECLARE
	// create and initialize the stack
	InitializeStack();
	POSITION step;
	int now_x, now_y, next_x, next_y;
	directions d;
	// start from (1, 1, E)
	step.x = 1;
	step.y = 1;
	step.dir = E;
	// if change extrange and exit manually
	if (Form1->CheckBox1->Checked)
	{
		step.x = Form1->Edit3->Text.ToInt() + 1;
		step.y = Form1->Edit4->Text.ToInt() + 1;
		step.dir = N;
	}
	int start_x = step.x;
	int start_y = step.y;
	push(step);
	maze[step.x][step.y] = 5;
	bool border = true;
    InitializeStringGrid(border);
	// while stack NOT empty
	while (top != -1)
	{
		step = pop();
		now_x = step.x;
		now_y = step.y;
		d = step.dir;
		// try all the directions
		while (d <= 7)
		{
			// (now_x, now_y) sill have the to choice move
			next_x = now_x + movement[d].dx;
			next_y = now_y + movement[d].dy;
			// (next_x, next_y) has not been passed, and there is available to pass
			if (maze[next_x][next_y] == 0 || (maze[next_x][next_y] == 5 && next_x != start_x && next_y != start_y))
			{
				step.x = now_x;
				step.y = now_y;
				step.dir = (directions)(d + 1);
				push(step);
				// if the next step is exit, means find the exit successfully.
				if (maze[next_x][next_y] == 5)
				{
					// find the exit successfully, so printing the path and it is time to stop
					// Pop all the elements in stack and you will get the path from extance to exit
					while (top-- > 1)
					{
						step = pop();
						// 3: passed
						maze[step.x][step.y] = 3;
					}
					// initialize top for secure
					top = -1;
					Form1->Memo1->Lines->Add("Result:");
					// print the maze with border
					PrintMaze(border);
					Form1->Memo1->Lines->Add("Exit the maze!");
					// refresh StringGrids
					if (!(Form1->CheckBox3->Checked))
						RefreshStringGrid(border);
					// delete and free stack's memory
					DeleteStack();
					return;
				}
				// 3: passed
				maze[next_x][next_y] = 3;
				// refresh StringGrids
				if (Form1->CheckBox3->Checked)
					RefreshStringGrid(border);
				// iterate
				now_x = next_x;
				now_y = next_y;
				d = N;
			}
			else
				// try next direction
				d = (directions)(d + 1);
		}
		// 4: passed and abandonned
		if (maze[now_x][now_y] != 5)
		{
			maze[now_x][now_y] = 4;
			// refresh StringGrids
			if (Form1->CheckBox3->Checked)
				RefreshStringGrid(border);
		}
	}
	while (top-- > 1)
	{
		step = pop();
		// 4: passed and abandonned
		maze[step.x][step.y] = 4;
	}
    // initialize top for secure
	top = -1;
	Form1->Memo1->Lines->Add("Result:");
	// print the maze with border
	PrintMaze(border);
	Form1->Memo1->Lines->Add("There is no path to exit the maze!");
	// refresh StringGrids
	if (Form1->CheckBox3->Checked)
		RefreshStringGrid(border);
	// delete and free stack's memory
	DeleteStack();
}

// Scanning effect with animation
void ScanAnimation()
{
    if (Form1->CheckBox4->Checked)
		Form1->DoubleBuffered = true;
	else
		Form1->DoubleBuffered = false;
	for (int i = 0; i < row + 2; i++)
    {
		for (int j = 0; j < col + 2; j++)
		{
			Sleep(Form1->TrackBar1->Position);
			int k = Form1->StringGrid1->Cells[j][i].ToInt();
			Form1->StringGrid1->Cells[j][i] = 6;
            // refresh
			Form1->StringGrid1->Refresh();
			Form1->StringGrid2->Refresh();
			Form1->StringGrid3->Refresh();
			Form1->StringGrid4->Refresh();
			Form1->StringGrid5->Refresh();
			Form1->StringGrid6->Refresh();
			Form1->StringGrid1->Cells[j][i] = k;
		}
	}
}

