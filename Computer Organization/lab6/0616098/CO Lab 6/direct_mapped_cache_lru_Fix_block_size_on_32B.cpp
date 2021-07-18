#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;

struct cache_content{
	bool v;
	unsigned int  tag;
//	unsigned int	data[16];
	unsigned int cnt;
};

const int K = 1024;

void simulate(int cache_size, int ways, char *name)
{
	int set_size =  cache_size / ways;		//calculate number of sets
	int block_size = 32;
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
	while(fscanf(fp, "%x", &x) != EOF)
    {
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
		}
		else                        //hit -> bring hit cnt to highest and adjust larger cnt (newer) to decrease one
        {
			for(int i = 0; i < ways; i++)
				if(i != idx_search && cache[index][i].cnt > cache[index][idx_search].cnt)   //newer then target
					cache[index][i].cnt--;
			cache[index][idx_search].cnt = ways - 1;
			hit++;
		}
	}

	fclose(fp);
	double miss_rate = (double)miss / (double)(hit + miss) * 100;
	printf("%uK\t\t%-10u\t%-10u\t%-10u\t%-.10f\t%\n", cache_size / K, ways, hit, miss, miss_rate);
	delete [] cache;
}

int main()
{
	// Let us simulate 4KB cache with 16B blocks
	printf("%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n", "Cache size", "Ways", "Hit", "Miss", "Miss Rate");
	for(int cache_size = 1; cache_size <= 32; cache_size <<= 1)
		for(int associativity = 1; associativity <= 8; associativity <<= 1)
			simulate(cache_size * K, associativity, "Trace.txt");
	return 0;
}
