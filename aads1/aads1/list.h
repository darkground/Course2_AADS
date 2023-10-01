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
public:
    LinkedList(unsigned n = 0);
    LinkedNode* at(unsigned);
    LinkedNode* insert(unsigned, int v);
    LinkedNode* append(int v);
    void clear();
    void remove(unsigned);
    void swap(unsigned, unsigned);
    unsigned size();
    unsigned length();

    friend std::ostream& operator<<(std::ostream&, LinkedList);
};
