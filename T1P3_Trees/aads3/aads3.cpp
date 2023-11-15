#include <iostream>
#include "tree.h"
#include "avl.h"

using namespace std;

/*
*   Функция для ввода данных в терминал
*   При вызове функции нужно указать получаемые данные в скобках,
*   т.е. readValue<int>() - получить число.
*   prompt - текст перед вводом
*   value - значение для заполнения
*/
template <typename T>
T readValue(const char* prompt = "") {
    T value = 0;
    cout << prompt;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cout << "Incorrect input. Enter new value: ";
            cin.clear();
            // numeric_limits<streamsize> это предел количества знаков в streamsize (вернёт число)
            // нужно чтобы очистить максимальное количество оставшихся символов в буфере до новой строки
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

int main()
{
    char choice;
    do {
        choice = readValue<char>("Read from file or console? (c/f): ");
    } while (choice != 'c' && choice != 'f');

    Tree* t;
    if (choice == 'c') {
        string v;
        while (true) {
            try {
                cout << "Input: ";
                getline(cin, v);
                t = new Tree(v);
                break;
            }
            catch (runtime_error e) {
                cout << "Parse error: " << e.what() << endl;
            }
        }
    }
    else { t = new Tree(0); }

    TreeAVL avl(t->walk());
    while (true) {
        system("cls");
        cout << "AVL Tree:\n" << avl;
        cout <<
            "Choose a category from below:\n"
            "0. Exit\n"
            "1. Insert element into AVL\n"
            "2. Delete element from AVL\n"
            "3. Search element in AVL\n"
            "4. Straight AVL walk\n"
            "5. Reverse AVL walk\n"
            "6. Symmetrical AVL walk\n"
            "7. Wide AVL walk\n\n";
        int choice = readValue<int>("Type a number to continue: ");
        cout << endl;
        switch (choice) {
            case 0:
                return 0;
            case 1: {
                int n = readValue<int>("Input a number to insert: ");
                avl.add(n);
                break;
            }
            case 2: {
                int n = readValue<int>("Input a number to delete: ");
                avl.remove(n);
                break;
            }
            case 3: {
                int n = readValue<int>("Input a number to search: ");
                TreeAVLNode* node = avl.search(n);
                if (node != NULL)
                    cout << "Element found: " << node->value << endl;
                else
                    cout << "Element not found" << endl;
                break;
            }
            case 4:
                for (int i : avl.strw())
                    cout << i << ' ';
                cout << endl;
                break;
            case 5:
                for (int i : avl.revw())
                    cout << i << ' ';
                cout << endl;
                break;
            case 6:
                for (int i : avl.symw())
                    cout << i << ' ';
                cout << endl;
                break;
            case 7:
                for (int i : avl.widew())
                    cout << i << ' ';
                cout << endl;
                break;
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
                break;
        }
        system("pause");
    }
}