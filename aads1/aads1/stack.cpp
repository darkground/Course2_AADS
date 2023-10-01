#include <iostream>
#include <fstream>
#include "stack.h"

Stack::Stack() {
	head = 0;
	len = 0;
}

/*
* Вернуть длину стека.
*/
unsigned Stack::size() {
	return len;
}

/*
* Пересчитать длину стека.
*/
unsigned Stack::length() {
	unsigned length = 0;
	StackNode* node = head;
	while (node) {
		length++;
		node = node->next;
	}
	return length;
}

/*
* Получить верхний элемент стека.
*/
string Stack::front() {
	return head->value;
}

/*
* Получить нижний элемент стека.
*/
string Stack::back() {
	if (head == 0)
		return 0;
	StackNode* h = head;
	while (h->next)
		h = h->next;
	return h->value;
}

/*
* Добавить элемент наверх стека.
*/
void Stack::push(string data) {
	StackNode* nnode = new StackNode;
	nnode->value = data;
	nnode->next = head;
	head = nnode;
	len++;
}

/*
* Добавить элемент вниз стека.
*/
void Stack::pushBack(string data) {
	if (head == 0)
		return push(data);

	StackNode* tail = head;
	while (tail->next)
		tail = tail->next;
	
	StackNode* nnode = new StackNode;
	nnode->value = data;
	nnode->next = 0;
	tail->next = nnode;
	len++;
}

/*
* Взять элемент сверху стека.
*/
string Stack::pop() {
	if (head == 0)
		return 0;
	len--;
	
	StackNode* front = head;
	string v = front->value;
	head = head->next;
	delete front;
	return v;
}

/*
* Взять элемент снизу стека.
*/
string Stack::popBack() {
	if (head == 0 || head->next == 0)
		return pop();
	len--;

	StackNode* butOne = head;
	while (butOne->next && butOne->next->next)
		butOne = head->next;	

	StackNode* bottom = butOne->next; 
	string v = bottom->value;
	butOne->next = 0;
	delete bottom;
	return v;
}

void Stack::clear() {
	StackNode* prev = 0;
	while (head->next) {
		prev = head;
		head = head->next;
		delete prev;
	}
	delete head;
}

ostream& operator<<(ostream& os, Stack s) {
	StackNode* h = s.head;
	while (h) {
		os << h->value << " ";
		h = h->next;
	}
	return os;
}