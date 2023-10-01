#pragma once

class Vector {
	int* arr;
	unsigned capacity;
	unsigned length;
public:
	Vector(unsigned = 1);
	void clear();
	void resize(unsigned);
	int at(unsigned);
	unsigned size();
	unsigned cap();
	void insert(unsigned, int);
	void append(int);
	void remove(unsigned);
	void swap(unsigned, unsigned);
};