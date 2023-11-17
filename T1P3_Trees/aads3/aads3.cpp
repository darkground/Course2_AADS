#include <iostream>
#include <sstream>
#include <fstream>
#include "tree.h"
#include "avl.h"
#include "bt.h"

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

Tree* tree_menu() {
    char choice;
    do {
        choice = readValue<char>("Read tree from file or console? (c/f): ");
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
    else {
        while (true) {
            ifstream ifs("input.txt");
            if (!ifs.is_open()) {
                cout << "File not found" << endl;
            } else {
                try {
                    stringstream buffer;
                    buffer << ifs.rdbuf();
                    t = new Tree(buffer.str());
                    break;
                }
                catch (runtime_error e) {
                    cout << "Parse error: " << e.what() << endl;
                }
                ifs.close();
            }
            system("pause");
        }
    }
    return t;
}

void binary_menu(std::vector<int> el) {
    TreeBinary bt(el);
    while (true) {
        system("cls");
        cout << "Binary Tree:\n" << bt;
        cout <<
            "\nChoose a category from below:\n"
            "0. Back to structures\n"
            "1. Insert element into BT\n"
            "2. Delete element from BT\n"
            "3. Search element in BT\n"
            "4. Straight BT walk\n"
            "5. Reverse BT walk\n"
            "6. Symmetrical BT walk\n"
            "7. Wide BT walk\n\n";
        int choice = readValue<int>("Type a number to continue: ");
        cout << endl;
        switch (choice) {
            case 0:
                return;
            case 1: {
                int n = readValue<int>("Input a number to insert: ");
                bt.add(n);
                break;
            }
            case 2: {
                int n = readValue<int>("Input a number to delete: ");
                bt.remove(n);
                break;
            }
            case 3: {
                int n = readValue<int>("Input a number to search: ");
                TreeBinaryNode* node = bt.search(n);
                if (node != NULL)
                    cout << "Element found: " << node->value << endl;
                else
                    cout << "Element not found" << endl;
                break;
            }
            case 4:
                for (int i : bt.strw())
                    cout << i << ' ';
                cout << endl;
                break;
            case 5:
                for (int i : bt.revw())
                    cout << i << ' ';
                cout << endl;
                break;
            case 6:
                for (int i : bt.symw())
                    cout << i << ' ';
                cout << endl;
                break;
            case 7:
                for (int i : bt.widew())
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

void avl_menu(std::vector<int> el) {
    TreeAVL avl(el);
    while (true) {
        system("cls");
        cout << "AVL Tree:\n" << avl;
        cout <<
            "\nChoose a category from below:\n"
            "0. Back to structures\n"
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
                return;
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

int choose_menu(Tree* t) {
    while (true) {
        system("cls");
        cout << "Simple tree:\n" << *t;
        cout <<
            "\nChoose structure:\n"
            "0. Exit\n"
            "1. Re-enter tree\n"
            "2. Binary trees\n"
            "3. AVL trees\n\n";
        int choice = readValue<int>("Type a number to continue: ");
        cout << endl;
        switch (choice) {
            case 0:
                return 1;
            case 1:
                return 0;
            case 2:
                binary_menu(t->walk());
                break;
            case 3:
                avl_menu(t->walk());
                break;
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
                break;
        }
        system("pause");
    }
}

int main()
{
    while (true) {
        system("cls");
        Tree* t = tree_menu();
        if (choose_menu(t)) return 0;
    }
}