#pragma once
#include <string>
#include <ostream>

struct StackNode {
	std::string value;
	StackNode* next;
};

class Stack {
	unsigned len;
	StackNode* head;
public:
	Stack();
	unsigned size();
	unsigned length();
	void clear();
	std::string front();
	std::string back();
	
	void push(std::string);
	std::string pop();
	void pushBack(std::string);
	std::string popBack();

	friend std::ostream& operator<<(std::ostream&, Stack);
};