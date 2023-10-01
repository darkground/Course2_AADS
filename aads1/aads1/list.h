#pragma once

struct Node {
    int data = 0;
    Node* prev = 0;
    Node* next = 0;
};

class LinkedList {
private:
    unsigned len;
    Node* head;
public:
    LinkedList(unsigned n = 0);
    Node* at(unsigned);
    Node* insert(unsigned, int v);
    Node* append(int v);
    void clear();
    void remove(unsigned);
    void swap(unsigned, unsigned);
    unsigned size();
    unsigned length();
};
