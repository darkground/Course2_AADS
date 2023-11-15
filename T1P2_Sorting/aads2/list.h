#pragma once
#include <ostream>

struct LinkedNode {
    int value = 0;
    LinkedNode* prev = 0;
    LinkedNode* next = 0;
};

enum SortingAlgorithm {
    MERGE = 0,
    TIM = 1,
    INSERTION = 2,
    RADIXLSD = 3
};

class LinkedList {
    unsigned len;
    LinkedNode* head;

    LinkedNode* node_at(unsigned);

    int minrun();
    int bSearch(int, int, int);
    void merge(int, int, int);
    void timMerge(int, int, int);
    void mergeSort(int, int);
    void insertionSort(int, int);
    void timSort();
    void radixLSDSort();
public:
    LinkedList(unsigned n = 0);
    LinkedList(std::initializer_list<int>);
    ~LinkedList();

    unsigned size();
    unsigned length();
    void clear();
    int& at(unsigned);
    int search(int);
    int bSearch(int);
    int max();
    int min();

    void random(unsigned, int, int = 0);
    void insert(unsigned, int v);
    void append(int v);
    void remove(unsigned);
    void remove(int);
    void swap(unsigned, unsigned);
    void swap(int, int);
    void reverse();
    void reverse(unsigned, unsigned);
    void sort(SortingAlgorithm);

    int& operator[](unsigned);
    friend std::ostream& operator<<(std::ostream&, LinkedList&);
};
