#include <string>

using namespace std;

struct StackNode {
	string value;
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
	string front();
	string back();
	
	void push(string);
	string pop();
	void pushBack(string);
	string popBack();

	friend ostream& operator<<(ostream&, Stack);
};