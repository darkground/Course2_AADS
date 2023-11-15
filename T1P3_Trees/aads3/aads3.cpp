#include <iostream>
#include "bt.h"

using namespace std;

int main()
{
    string v;
    while (true) {
        try {
            getline(cin, v);
            TreeBinary bt(v);
            cout << bt;
        }
        catch (runtime_error e) {
            cout << "parse error " << e.what() << endl;
        }
    }
}