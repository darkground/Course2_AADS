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

	void resize(unsigned);
	void insert(unsigned, int);
	void append(int);
	void remove(unsigned);
	void swap(unsigned, unsigned);

	friend std::ostream& operator<<(std::ostream&, Vector);
};