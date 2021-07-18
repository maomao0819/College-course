#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;

struct cache_content{
	bool v;
	unsigned int  tag;
//	unsigned int	data[16];
};

const int K = 1024;

void simulate(int cache_size, int block_size, char *name){
	unsigned int tag, index, x, miss = 0, hit = 0;

	int offset_bit = (int) log2(block_size);
	int index_bit = (int) log2(cache_size / block_size);
	int line = cache_size >> (offset_bit);      //same as cache_size/block_size

	cache_content *cache = new cache_content[line];
	//cout << "cache line:" << line << endl;
    //initialize valid bit to false
	for(int j = 0; j < line; j++)
		cache[j].v = false;

    FILE * fp = fopen(name, "r");					//read file
    if(fp == NULL){
		cout << "File error" << endl;
		return;
	}
	while(fscanf(fp, "%x", &x)!=EOF){
		//cout << hex << x << "\n";
		index = (x >> offset_bit) & (line - 1);     //mod
		tag = x >> (index_bit + offset_bit);
		if(cache[index].v && cache[index].tag == tag){
			cache[index].v=true; 			//hit
			hit++;
		}
		else{
			cache[index].v = true;			//miss
			cache[index].tag = tag;
			miss++;
		}
	}
	fclose(fp);
	double miss_rate = (double)miss / (double)(hit + miss) * 100;
    printf("%-10u\t%-10u\t%-10u\t%-10u\t%-.10f\t%\n", cache_size, block_size, hit, miss, miss_rate);
	delete [] cache;
}

int main()
{
	// Let us simulate 4KB cache with 16B blocks
	//simulate(4*K, 16, "trace.txt");
	printf("%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n", "Cache size", "Block Size", "Hit", "Miss", "Miss Rate");
	for(int cache_size = 64; cache_size <= 512; cache_size <<= 1)
		for(int block_size = 1; block_size <= 32; block_size <<= 1)
			simulate(cache_size, block_size, "Trace.txt");
	return 0;
}
