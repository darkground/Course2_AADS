#include "stack.h"

Stack::Stack() {
	head = 0;
	len = 0;
}

/*
* Деструктор стека
*/
Stack::~Stack() {
    clear();
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
std::string Stack::front() {
	if (head == 0)
		throw std::runtime_error("Head was null");
	return head->value;
}

/*
* Получить нижний элемент стека.
*/
std::string Stack::back() {
	if (head == 0)
		throw std::runtime_error("Head was null");
	StackNode* h = head;
	while (h->next)
		h = h->next;
	return h->value;
}

/*
* Добавить элемент наверх стека.
*/
void Stack::push(std::string data) {
	StackNode* nnode = new StackNode;
	nnode->value = data;
	nnode->next = head;
	head = nnode;
	len++;
}

/*
* Добавить элемент вниз стека.
*/
void Stack::pushBack(std::string data) {
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
std::string Stack::pop() {
	if (head == 0)
		throw std::runtime_error("Head was null");
	len--;
	
	StackNode* front = head;
	std::string v = front->value;
	head = head->next;
	delete front;
	return v;
}

/*
* Взять элемент снизу стека.
*/
std::string Stack::popBack() {
	if (head == 0 || head->next == 0)
		return pop();
	len--;

	StackNode* butOne = head;
	while (butOne->next && butOne->next->next)
		butOne = butOne->next;

	StackNode* bottom = butOne->next; 
	std::string v = bottom->value;
	butOne->next = 0;
	delete bottom;
	return v;
}

void Stack::clear() {
	if (len == 0)
		return;
	StackNode* next = 0;
	StackNode* current = head;
	while (current) {
		next = current->next;
		delete current;
		current = next;
	}
	head = 0;
	len = 0;
}

std::ostream& operator<<(std::ostream& os, Stack& s) {
	os << "Stack[";
	StackNode* h = s.head;
	if (s.head != 0)
		while (true) {
			os << h->value;
			if (h->next) {
				os << ", ";
				h = h->next;
			} else break;
		}
	os << "]";
	return os;
}