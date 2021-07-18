#pragma once

class Increment
{
public:
	Increment(int c = 0, int i = 1);
	~Increment();
	void print() const;
private:
	int count;
	const int increment;
};

