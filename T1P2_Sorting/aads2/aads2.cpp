#include <iostream>
#include "vector.h"

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

int main() {
    Vector ll;

    while (true) {
        system("cls");
        cout << ll << " (size " << ll.size() << ")" << endl;
        cout <<
            "Sortings - Choose an action from below:\n"
            "0. Back\n"
            "1. Array continuous input\n"
            "2. Array random\n"
            "3. Append element\n"
            "4. Insert element\n"
            "5. Remove element by index\n"
            "6. Remove element by value\n"
            "7. Clear\n"
            "8. Element at\n"
            "9. Search\n"
            "10. Swap by index\n"
            "11. Swap by value\n"
            "\n--- Sortings --\n"
            "12. Timsort\n"
            "13. Merge sort\n"
            "14. Insertion sort\n"
            "15. Radix LSD sort\n\n";
        int choice = readValue<int>("Type a number to continue: ");
        cout << endl;
        try {
            switch (choice) {
                case 0: return 0;
                case 1: {
                    int value = 0;
                    cout << "Enter a number or anything else to cancel...\n";
                    while (true) {
                        cout << ll << endl << "Input: ";
                        cin >> value;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        else {
                            ll.append(value);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    }
                    break;
                }
                case 2: {
                    unsigned v = readValue<unsigned>("Enter amount: ");
                    int mn = readValue<int>("Enter min: ");
                    int mx = readValue<int>("Enter max: ");
                    ll.random(v, mx, mn);
                    break;
                }
                case 3: {
                    int v = readValue<int>("Enter integer: ");
                    ll.append(v);
                    break;
                }
                case 4: {
                    int v = readValue<int>("Enter integer: ");
                    unsigned i = -1;
                    do {
                        i = readValue<unsigned>("Enter index: ");
                    } while (i < 0 || i > ll.size());
                    ll.insert(i, v);
                    break;
                }
                case 5: {
                    if (ll.size() == 0) {
                        cout << "Nothing to delete" << endl;
                        break;
                    }
                    unsigned i = -1;
                    do {
                        i = readValue<unsigned>("Enter index: ");
                    } while (i < 0 || i >= ll.size());
                    ll.remove(i);
                    break;
                }
                case 6: {
                    if (ll.size() == 0) {
                        cout << "Nothing to delete" << endl;
                        break;
                    }
                    int v = readValue<int>("Enter integer: ");
                    ll.remove(v);
                    break;
                }
                case 7:
                    ll.clear();
                    break;
                case 8: {
                    unsigned i;
                    do {
                        i = readValue<unsigned>("Enter index: ");
                    } while (i < 0 || i >= ll.size());
                    cout << "Element at " << i << ": " << ll.at(i) << endl;
                    break;
                }
                case 9: {
                    if (ll.size() == 0) {
                        cout << "Nothing to delete" << endl;
                        break;
                    }
                    int v = readValue<int>("Enter integer: ");
                    cout << "Index is: " << ll.search(v) << endl;
                    break;
                }
                case 10: {
                    unsigned i1, i2;
                    do {
                        i1 = readValue<unsigned>("Enter index 1: ");
                    } while (i1 < 0 || i1 >= ll.size());
                    do {
                        i2 = readValue<unsigned>("Enter index 2: ");
                    } while (i2 < 0 || i2 >= ll.size() || i1 == i2);
                    ll.swap(i1, i2);
                    break;
                }
                case 11: {
                    int v1 = readValue<int>("Enter value 1: ");
                    int v2;
                    do {
                        v2 = readValue<int>("Enter value 2: ");
                    } while (v1 == v2);
                    ll.swap(v1, v2);
                    break;
                }
                case 12: {
                    ll.sort(SortingAlgorithm::TIM);
                    break;
                }
                case 13: {
                    ll.sort(SortingAlgorithm::MERGE);
                    break;
                }
                case 14: {
                    ll.sort(SortingAlgorithm::INSERTION);
                    break;
                }
                case 15: {
                    ll.sort(SortingAlgorithm::RADIXLSD);
                    break;
                }
                default:
                    cout << "\nCategory with number " << choice << " does not exist." << endl;
                    break;
            }
        } catch (std::runtime_error e) {
            cout << "\nRuntime error: " << e.what() << endl;
        }
        system("pause");
    }
}