//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HW7_Shortest_Path.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

// DEFINE MACRO
#define max_matrix_length 100

// using global variable to pass value easily
// 2d-array to record the weight
int Weight[max_matrix_length][max_matrix_length];
// Weight-matrix size
int n = 0;
// the value of the disconnected weights
int disconnected_weight = 99999;
bool is_graph_created = false;
bool is_print_detail = false;

// PROTOTYPE DECLARATION
// create and initialize the graph.
void CreateGraph(int n, int range_weight, int threshold_weight, int disconnected_weight, int min_n_weights, bool directed);
// load the txt file into the graph.
void LoadGraph();
// show error message if the graph has been created.
void CheckGraph();
// print adjacent graph on the stringgrid.
void PrintAdjacentGraph(int n);
// create SSAD's stringgrid.
void CreateSSADTable(int n);
// create APSP's stringgrid.
void CreateAllPairsTable(int n);
// create the stringgrid of transitive closure.
void CreateTransitiveClosureTable(int n, int disconnected_weight);
// initialize all the tables.
void InitializeTables(int n, int disconnected_weight);
// get the index of the min value in the array.
int min_index(int array [], int disconnected_weight);
// get the fit k which is the index of the min value except having been considered value in the array for Dijkstra.
int fit_k(int n, int disconnected_weight, int Distance [], bool found []);
// print SSAD's distance on the stringgrid.
void PrintSSADTableDistance(int n, int SSADTable_index, int Distance []);
// print SSAD's edge on the stringgrid.
void PrintSSADTableEdge(int n, int Edge []);
// print SSAD's detail on the memo.
void PrintSSADDistance(int source_number, int n, int Distance [], int Edge []);
// the algorithm for SSAD
void Dijkstra(int n, int disconnected_weight, int source_number);
// print APSP's distance on the stringgrid.
void PrintAllPairsTableDistance(int n, int ** A);
// print APSP's edge on the stringgrid.
void PrintAllPairsTableEdge(int n, int ** Edge);
// print APSP's detail on the memo.
void PrintAPSPDistance(int n, int ** A, int ** Edge);
// the algorithm for APSP
void APSP(int n, int disconnected_weight);
// print transitive closure on the stringgrid.
void PrintTransitiveClosureTableDistance(int n, int ** TC);
// the algorithm for transitive closure
void TransitiveClosure(int n, int disconnected_weight);

//---------------------------------------------------------------------------

// Initialize global variables
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	n = 0;
	disconnected_weight = 99999;
	is_graph_created = false;
	is_print_detail = false;
}
//---------------------------------------------------------------------------

// Load the txt file into the graph
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	LoadGraph();
	InitializeTables(n, disconnected_weight);
}
//---------------------------------------------------------------------------

// Create and initialize the graph
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	n = StrToInt(Edit1->Text);
	int range_weight = StrToInt(Edit2->Text);
	int threshold_weight = StrToInt(Edit3->Text);
	disconnected_weight = StrToInt(Edit4->Text);
	bool directed = Form1->CheckBox1->Checked ? false : true;
	int min_n_weights = StrToInt(Edit5->Text);
	CreateGraph(n, range_weight, threshold_weight, disconnected_weight, min_n_weights, directed);
	InitializeTables(n, disconnected_weight);
}
//---------------------------------------------------------------------------

// SSAD
void __fastcall TForm1::Button3Click(TObject *Sender)
{
    CheckGraph();
	if (is_graph_created)
	{
		int source_number = StrToInt(Edit6->Text);
		Dijkstra(n, disconnected_weight, source_number);
	}
}
//---------------------------------------------------------------------------

// All Pairs
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	CheckGraph();
	if (is_graph_created)
		APSP(n, disconnected_weight);
}
//---------------------------------------------------------------------------

// Transitive Closure
void __fastcall TForm1::Button5Click(TObject *Sender)
{
	CheckGraph();
	if (is_graph_created)
		TransitiveClosure(n, disconnected_weight);
}
//---------------------------------------------------------------------------

// FUNCTION DEFINITION
// create and initialize the graph.
void CreateGraph(int n, int range_weight, int threshold_weight, int disconnected_weight, int min_n_weights, bool directed)
{
	is_graph_created = true;
	srand(time(NULL));
	int n_connected_weights = n * n - n;
	for (int i = 0; i < n; i++)
	{
		// directed
		if (directed)
		{
			for (int j = 0; j < n; j++)
			{
				if (i != j)
				{
                    Weight[i][j] = rand() % range_weight + 1;
					if (Weight[i][j] > threshold_weight)
					{
						Weight[i][j] = disconnected_weight;
						n_connected_weights--;
					}
				}
			}
			Weight[i][i] = 0;
		}
		// undirected
		else
        {
			for (int j = 0; j < i; j++)
			{
				Weight[i][j] = rand() % range_weight + 1;
				if (Weight[i][j] > threshold_weight)
				{
					Weight[i][j] = disconnected_weight;
                    n_connected_weights -= 2;
				}
				Weight[j][i] = Weight[i][j];
			}
			Weight[i][i] = 0;
		}
	}
	 // generate enough weights
	if (n_connected_weights < min_n_weights)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (Weight[i][j] == disconnected_weight)
				{
					// directed
					if (directed)
					{
						Weight[i][j] = rand() % threshold_weight + 1;
						n_connected_weights++;
					}
					// undirected
					else
					{
						Weight[i][j] = rand() % threshold_weight + 1;
						Weight[j][i] = Weight[i][j];
						n_connected_weights += 2;
					}
				}
				if (n_connected_weights >= min_n_weights)
					break;
			}
            if (n_connected_weights >= min_n_weights)
				break;
		}
	}
}

// load the txt file into the graph.
void LoadGraph()
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
		// Read in 2 integers, n, disconnected_weight
		fscanf(fp, "%d", &n);
		fscanf(fp, "%d", &disconnected_weight);
		Form1->Edit1->Text = n;
		Form1->Edit4->Text = disconnected_weight;
		// Read  into the Weight[][]
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				fscanf(fp, "%d", &Weight[i][j]);
		fclose(fp);
	}
	is_graph_created = true;
}

// show error message if the graph has been created.
void CheckGraph()
{
	if (!is_graph_created)
		ShowMessage("The graph hasn't been created yet!");
}

// print adjacent graph on the stringgrid.
void PrintAdjacentGraph(int n)
{
	// create
	Form1->StringGrid1->RowCount = n + 1;
	Form1->StringGrid1->ColCount = n + 1;
	for (int i = 0; i < n; i++)
	{
		Form1->StringGrid1->Cells[i + 1][0] = i;
		Form1->StringGrid1->Cells[0][i + 1] = i;
		for (int j = 0; j < n; j++)
			Form1->StringGrid1->Cells[j + 1][i + 1] = Weight[i][j];
	}
	Form1->PageControl1->TabIndex = 1;
}

// create SSAD's stringgrid.
void CreateSSADTable(int n)
{
	// create
	Form1->StringGrid2->RowCount = n + 1;
	Form1->StringGrid2->ColCount = n + 2;
	// initialize
	for (int i = 0; i < n; i++)
	{
		Form1->StringGrid2->Cells[i + 1][0] = i;
		Form1->StringGrid2->Cells[0][i + 1] = i;
	}
	Form1->StringGrid2->Cells[n + 1][0] = "Find";
	Form1->PageControl1->TabIndex = 2;
}

// create APSP's stringgrid.
void CreateAllPairsTable(int n, int disconnected_weight)
{
	// create distance
	Form1->StringGrid3->RowCount = n + 1;
	Form1->StringGrid3->ColCount = n + 1;
	for (int i = 0; i < n; i++)
	{
		Form1->StringGrid3->Cells[i + 1][0] = i;
		Form1->StringGrid3->Cells[0][i + 1] = i;
		for (int j = 0; j < n; j++)
			Form1->StringGrid3->Cells[j + 1][i + 1] = Weight[i][j];
	}
	Form1->PageControl1->TabIndex = 3;

	// create edge
	Form1->StringGrid4->RowCount = n + 1;
	Form1->StringGrid4->ColCount = n + 1;
	for (int i = 0; i < n; i++)
	{
		Form1->StringGrid4->Cells[i + 1][0] = i;
		Form1->StringGrid4->Cells[0][i + 1] = i;
        for (int j = 0; j < n; j++)
		{
			Form1->StringGrid4->Cells[j + 1][i + 1] = i;
            if (Weight[i][j] == disconnected_weight)
				Form1->StringGrid4->Cells[j + 1][i + 1] = -1;
		}
	}
	Form1->PageControl1->TabIndex = 4;
}

// create the stringgrid of transitive closure.
void CreateTransitiveClosureTable(int n, int disconnected_weight)
{
	// create
	Form1->StringGrid5->RowCount = n + 1;
	Form1->StringGrid5->ColCount = n + 1;
	for (int i = 0; i < n; i++)
	{
		Form1->StringGrid5->Cells[i + 1][0] = i;
		Form1->StringGrid5->Cells[0][i + 1] = i;
		for (int j = 0; j < n; j++)
			if (Weight[i][j] != disconnected_weight)
				Form1->StringGrid5->Cells[j + 1][i + 1] = 1;
			else
				Form1->StringGrid5->Cells[j + 1][i + 1] = 0;
	}
	Form1->PageControl1->TabIndex = 5;
}

// initialize all the tables.
void InitializeTables(int n, int disconnected_weight)
{
    PrintAdjacentGraph(n);
	CreateSSADTable(n);
	CreateAllPairsTable(n, disconnected_weight);
	CreateTransitiveClosureTable(n, disconnected_weight);
    Form1->PageControl1->TabIndex = 1;
}

// get the index of the min value in the array.
int min_index(int array [], int disconnected_weight)
{
	int min = disconnected_weight;
	int min_id = -1;
	for (int i = 0; i < n; i++)
	{
		if (array[i] < min)
		{
			min = array[i];
			min_id = i;
		}
	}
	return min_id;
}

// get the fit k which is the index of the min value except having been considered value in the array for Dijkstra.
int fit_k(int n, int disconnected_weight, int Distance [], bool found [])
{
	int dist[n];
	for (int i = 0; i < n; i++)
		dist[i] = found[i] ? disconnected_weight : Distance[i];
	return min_index(dist, disconnected_weight);
}

// print SSAD's distance on the stringgrid.
void PrintSSADTableDistance(int n, int SSADTable_index, int Distance [])
{
	for (int i = 0; i < n; i++)
		Form1->StringGrid2->Cells[SSADTable_index + 1][i + 1] = Distance[i];
	Form1->PageControl1->TabIndex = 2;
}

// print SSAD's edge on the stringgrid.
void PrintSSADTableEdge(int n, int Edge [])
{
	for (int i = 0; i < n; i++)
		Form1->StringGrid2->Cells[n + 1][i + 1] = Edge[i];
	Form1->PageControl1->TabIndex = 2;
}

// print SSAD's detail on the memo.
void PrintSSADDistance(int source_number, int n, int Distance [], int Edge [])
{
	int u = source_number;
	for (int v = 0; v < n; v++)
	{
		String output = "";
		output = IntToStr(v);
		int current;
		int next;
		for (next = v, current = Edge[next]; current != u; next = current, current = Edge[next])
		{
			if (current == -1)
				break;
			output = IntToStr(current) + " --[" + IntToStr(Weight[current][next])+ "]--> " + output;
		}
		if (current != -1)
			Form1->Memo1->Lines->Add("The shortest distance from " + IntToStr(u) + " to " + IntToStr(v) + " is " + IntToStr(Distance[v]) + " with the path " + IntToStr(u) + " --[" + IntToStr(Weight[u][next]) + "]--> " + output + ".");
		else
			Form1->Memo1->Lines->Add(IntToStr(u) + " can't reach " + IntToStr(v) + " .");
	}
	Form1->Memo1->Lines->Add("");
	Form1->PageControl1->TabIndex = 0;
}

// the algorithm for SSAD
void Dijkstra(int n, int disconnected_weight, int source_number)
{
	int u = source_number;
	int Distance[n];
	int Edge[n];
	// has been min value
	bool found[n];
	is_print_detail = Form1->CheckBox2->Checked;
	// first step
	for (int v = 0; v < n; v++)
	{
		Distance[v] = Weight[u][v];
		Edge[v] = Distance[v] == disconnected_weight ? -1 : u;
		found[v] = false;
	}
	found[u] = true;
	Distance[u] = 0;
	int SSADTable_index = 0;
	// print SSAD's distance on the stringgrid.
	PrintSSADTableDistance(n, 0, Distance);
	if (is_print_detail)
		Form1->Memo1->Lines->Add("SSAD");
	// iteration
	for (SSADTable_index = 1; SSADTable_index < n; SSADTable_index++)
	{
		// get the fit k which is the index of the min value except having been considered value in the array.
		int k = fit_k(n, disconnected_weight, Distance, found);
		// can't reach
		if (k == -1)
			break;
		found[k] = true;
		if (is_print_detail)
			Form1->Memo1->Lines->Add("min = " + IntToStr(k));
		for (int v = 0; v < n; v++)
		{
			// compare the distance passed or not passed by k
			if (found[v] == false && Distance[k] + Weight[k][v] < Distance[v])
			{
				Distance[v] = Distance[k] + Weight[k][v];
				Edge[v] = k;
			}
		}
		// print SSAD's distance on the stringgrid.
		PrintSSADTableDistance(n, SSADTable_index, Distance);
	}
	if (is_print_detail)
		// print SSAD's detail on the memo.
		PrintSSADDistance(source_number, n, Distance, Edge);
	while (SSADTable_index < n)
	{
		// print SSAD's distance on the stringgrid.
		PrintSSADTableDistance(n, SSADTable_index, Distance);
		SSADTable_index++;
	}
	// print SSAD's edge on the stringgrid.
	PrintSSADTableEdge(n, Edge);
}

// print APSP's distance on the stringgrid.
void PrintAllPairsTableDistance(int n, int ** A)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			Form1->StringGrid3->Cells[j + 1][i + 1] = A[i][j];
	Form1->PageControl1->TabIndex = 3;
}

// print APSP's edge on the stringgrid.
void PrintAllPairsTableEdge(int n, int ** Edge)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			Form1->StringGrid4->Cells[j + 1][i + 1] = Edge[i][j];
	Form1->PageControl1->TabIndex = 4;
}

// print APSP's detail on the memo.
void PrintAPSPDistance(int n, int ** A, int ** Edge)
{
	if (is_print_detail)
		Form1->Memo1->Lines->Add("APSP");
	for (int u = 0; u < n; u++)
	{
		Form1->Memo1->Lines->Add("u = " + IntToStr(u));
		for (int v = 0; v < n; v++)
		{
			String output = "";
			output = IntToStr(v);
			int current;
			int next;
			for (next = v, current = Edge[u][next]; current != u; next = current, current = Edge[u][next])
			{
				if (current == -1)
					break;
				output = IntToStr(current) + " --[" + IntToStr(Weight[current][next])+ "]--> " + output;
			}
			if (current != -1)
				Form1->Memo1->Lines->Add("The shortest distance from " + IntToStr(u) + " to " + IntToStr(v) + " is " + IntToStr(A[u][v]) + " with the path " + IntToStr(u) + " --[" + IntToStr(Weight[u][next]) + "]--> " + output + ".");
			else
				Form1->Memo1->Lines->Add(IntToStr(u) + " can't reach " + IntToStr(v) + " .");
		}
	}
	Form1->Memo1->Lines->Add("");
	Form1->PageControl1->TabIndex = 0;
}

// the algorithm for APSP
void APSP(int n, int disconnected_weight)
{
	is_print_detail = Form1->CheckBox2->Checked;
	// distance
	int ** A;
	A = new int *[n];
	for (int i = 0; i < n; i++)
		A[i] = new int[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			A[i][j] = Weight[i][j];
    // edge
	int ** E;
	E = new int *[n];
	for (int i = 0; i < n; i++)
		E[i] = new int[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			E[i][j] = Weight[i][j] == disconnected_weight ? -1 : i;

	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (A[i][j] > (A[i][k] + A[k][j]))
				{
					A[i][j] = A[i][k] + A[k][j];
					E[i][j] = k;
					int current = k;
					while (E[current][j] != current)
					{
						E[i][j] = E[current][j];
						current = E[current][j];
					}
				}
			}
		}
	}
	// print APSP's edge on the stringgrid.
	PrintAllPairsTableEdge(n, E);
	// print APSP's distance on the stringgrid.
	PrintAllPairsTableDistance(n, A);
	if (is_print_detail)
		// print APSP's detail on the memo.
		PrintAPSPDistance(n, A, E);

	for(int i = 0; i < n; i++)
		delete [] A[i];
	delete [] A;
}

// print transitive closure on the stringgrid.
void PrintTransitiveClosureTableDistance(int n, int ** TC)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			Form1->StringGrid5->Cells[j + 1][i + 1] = TC[i][j];
	Form1->PageControl1->TabIndex = 5;
}

// the algorithm for transitive closure
void TransitiveClosure(int n, int disconnected_weight)
{
	int ** TC;
	TC = new int *[n];
	for(int i = 0; i < n; i++)
		TC[i] = new int[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (Weight[i][j] != disconnected_weight)
				TC[i][j] = 1;
			else
				TC[i][j] = 0;

	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (TC[i][k] && TC[k][j])
					TC[i][j] = 1;

	// print transitive closure on the stringgrid.
	PrintTransitiveClosureTableDistance(n, TC);

	for(int i = 0; i < n; i++)
		delete [] TC[i];
	delete [] TC;
}
