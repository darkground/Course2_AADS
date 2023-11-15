#pragma once
#include <ostream>

enum SortingAlgorithm {
    MERGE = 0,
    TIM = 1,
    INSERTION = 2,
    RADIXLSD = 3
};

class Vector {
	int* arr;
	unsigned capacity;
	unsigned length;

	int minrun();
    int bSearch(int, int, int);
    void merge(int, int, int);
    void timMerge(int, int, int);
    void mergeSort(int, int);
    void insertionSort(int, int);
    void timSort();
    void radixLSDSort();
public:
	Vector(unsigned = 1);
	~Vector();
	unsigned size();
	unsigned cap();
	void clear();
	int& at(unsigned);
	int search(int);
	int bSearch(int);
    int max();
    int min();

    void random(unsigned, int, int = 0);
	void resize(unsigned);
	void insert(unsigned, int);
	void append(int);
	void remove(unsigned);
	void remove(int);
	void swap(unsigned, unsigned);
	void swap(int, int);
	void reverse();
    void reverse(unsigned, unsigned);
    void sort(SortingAlgorithm);

    int& operator[](unsigned);
	friend std::ostream& operator<<(std::ostream&, Vector&);
};