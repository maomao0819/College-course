#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

struct cache_content{
	bool v;
	unsigned int  tag;
//	unsigned int	data[16];
	unsigned int cnt;
};

const int K = 1024;

void simulate(int cache_size, int block_size, int ways, char *name)
{
	int set_size =  cache_size / ways;		//calculate number of sets
	unsigned int tag, index, x, miss = 0, hit = 0;

	int offset_bit = (int) log2(block_size);
	int index_bit = (int) log2(set_size / block_size);
	int line = set_size >> (offset_bit);      //same as cache_size/block_size

	cache_content **cache = new cache_content* [line];
    //cout << "cache line:" << line << endl;
    //initialize
	for(int i = 0; i < line; i++)
    {
		cache[i] = new cache_content[ways];
		for(int j = 0; j < ways; j++)
		{
			cache[i][j].v = false;
			cache[i][j].cnt = j;		//default: 0 1 2 3, 0 is the oldest
		}
	}

    FILE * fp = fopen(name, "r");					//read file
    if(fp == NULL){
		cout << "File error" << endl;
		return;
	}
	vector <int> hit_instr;
	vector <int> miss_instr;
	int count = 0;
	while(fscanf(fp, "%x", &x) != EOF)
    {
		count++;
		// cout << hex << x << " ";
		index = (x >> offset_bit) & (line - 1);     //mod
		tag = x >> (index_bit + offset_bit);
		short int idx_search;
		for(idx_search = 0; idx_search < ways; idx_search++)
			if(cache[index][idx_search].v && cache[index][idx_search].tag == tag)
				break;

		if(idx_search >= ways)     //miss -> replace by LRU
        {
			for(int i = 0; i < ways; i++)		    //find 0 to replace
            {
				if(cache[index][i].cnt == 0)        //oldest
                {                               //replace
					cache[index][i].v = true;
					cache[index][i].tag = tag;
					cache[index][i].cnt = ways - 1;
				}
				else                            //update cnt
					cache[index][i].cnt--;
			}
			miss++;
			miss_instr.push_back(count);
		}
		else                        //hit -> bring hit cnt to highest and adjust larger cnt (newer) to decrease one
        {
			for(int i = 0; i < ways; i++)
				if(i != idx_search && cache[index][i].cnt > cache[index][idx_search].cnt)   //newer then target
					cache[index][i].cnt--;
			cache[index][idx_search].cnt = ways - 1;
			hit++;
			hit_instr.push_back(count);
		}
	}

	fclose(fp);
	cout << "Hits instructions: " << hit_instr[0];
	for(int i = 1; i < hit_instr.size(); i++)
        cout << ", " << hit_instr[i];
    cout << "\n";
	cout << "Misses instructions: 1";
	for(int i = 1; i < miss_instr.size(); i++)
        cout << ", " << miss_instr[i];
    cout << "\n";
	double miss_rate = (double)miss / (double)(hit + miss) * 100;
	cout << "Miss rate: " << miss_rate << "%";
	delete [] cache;
}

int main()
{
	// Let us simulate 4KB cache with 16B blocks
	short int data_op;
	cout << "Input: 1...Trace1.txt, 2...Trace.txt : ";
	cin >> data_op;
	int cache_size, block_size, associativity;
	cout << "cache size (bytes) = ";
	cin >> cache_size;
	cout << "block size (bytes) = ";
	cin >> block_size;
	cout << "associativity      = ";
	cin >> associativity;
	cout << "\n";
    if(data_op == 1)
        simulate(cache_size, block_size, associativity, "Trace1.txt");
    else if(data_op == 2)
        simulate(cache_size, block_size, associativity, "Trace.txt");
	return 0;
}
