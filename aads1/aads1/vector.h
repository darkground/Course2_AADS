#pragma once
#include <ostream>

class Vector {
	int* arr;
	unsigned capacity;
	unsigned length;
public:
	Vector(unsigned = 1);
	unsigned size();
	unsigned cap();
	void clear();
	int at(unsigned);
	int search(int);

	void resize(unsigned);
	void insert(unsigned, int);
	void append(int);
	void remove(unsigned);
	void remove(int);
	void swap(unsigned, unsigned);
	void swap(int, int);

	friend std::ostream& operator<<(std::ostream&, Vector);
};