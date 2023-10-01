#include <iostream>
#include "list.h"
#include "vector.h"

using namespace std;

int main()
{
    auto x = LinkedList();
    x.append(1);
    x.append(2);
    x.append(4);
    for (unsigned i = 0; i < x.size(); i++)
        cout << x.at(i)->data << endl;
    auto y = Vector(10);
    y.append(1);
    y.append(2);
    y.append(4);
    for (unsigned i = 0; i < y.size(); i++)
        cout << y.at(i) << endl;
    std::cout << "Hello World!\n";
}