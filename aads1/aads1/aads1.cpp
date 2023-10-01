#include <iostream>
#include "list.h"
#include "vector.h"
#include "stack.h"

using namespace std;

int main()
{
	auto l = LinkedList();
	l.append(1);
	l.append(2);
	l.append(3);
	l.append(4);
	l.append(5);
	l.remove(6);
	cout << l;
}