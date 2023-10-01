#pragma once
#include <ostream>

struct LinkedNode {
    int value = 0;
    LinkedNode* prev = 0;
    LinkedNode* next = 0;
};

class LinkedList {
private:
    unsigned len;
    LinkedNode* head;

    LinkedNode* node_at(unsigned);
public:
    LinkedList(unsigned n = 0);
    unsigned size();
    unsigned length();
    void clear();
    int at(unsigned);

    void insert(unsigned, int v);
    void append(int v);
    void remove(unsigned);
    void swap(unsigned, unsigned);

    friend std::ostream& operator<<(std::ostream&, LinkedList);
};
