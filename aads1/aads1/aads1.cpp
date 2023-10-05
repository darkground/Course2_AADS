#include <iostream>
#include <vector>
#include <map>
#include "list.h"
#include "vector.h"
#include "stack.h"
#include <unordered_map>

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

/*
*   Функция для ввода данных в терминал (как строку)
*   prompt - текст перед вводом
*   line - строка для заполнения
*/
void readLine(const char* prompt, string* line) {
    cout << prompt;
    if (!getline(cin, *line)) {
        // Так как определённый тип не требуется, то при остатке символов в буфере просто очищаем их
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

const string OPS_ALL[] = {
    "**", "*", "/", "-", "+", "^",
    "(", ")",
    "sin", "cos", "tan", "cot"
};

const string OPS_FUNC[] = {
    "sin", "cos", "tan", "cot"
};

const map<string, int> OPS_WEIGHTS = { 
    {"+", 1},
    {"-", 1},
    {"*", 2},
    {"/", 2},
	{"^", 3},
    {"**", 3}, //same as ^
    {"(", 0},
    {")", 0},
    {"sin", 4},
    {"cos", 4},
    {"tan", 4},
    {"cot", 4},
};

bool isOperation(const string& str) {
	return find(begin(OPS_ALL), end(OPS_ALL), str) != end(OPS_ALL);
}

bool isFunc(const string& str) {
	return find(begin(OPS_FUNC), end(OPS_FUNC), str) != end(OPS_FUNC);
}

bool isNumber(const string& str) {
    string::const_iterator it = str.begin();
    while (it != str.end() && (isdigit(*it) || *it == '.')) ++it;
    return !str.empty() && it == str.end();
}

bool shouldMove(string token, Stack opstack) {
	return OPS_WEIGHTS.find(opstack.front())->second >= OPS_WEIGHTS.find(token)->second;
}

bool contains(string s, string sub, unsigned at) {
    for (unsigned i = at; i < s.size() && (i - at) < sub.size(); i++)
        if (s[i] != sub[i - at])
            return false;
    return true;
}

string vecToString(vector<string> v) {
    string result_s;
    for (string& tok : v)
        result_s += tok + ' ';
    return result_s;
}

double operation(std::string op, double a, double b) {
    switch (op[0]) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return op.size() > 1 ? pow(a, b) : a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        case 's': return sin(a);
        case 'c': return op[2] == 's' ?  cos(a) : (1 / tan(a));
        case 't': return tan(a);
        default: return 0;
    }
}

double compute(vector<string> rpn) {
	Stack outStack;
    for (auto& token : rpn) {
        cout << token << " " << outStack << endl;
        if (isNumber(token))
			outStack.pushBack(token);
        else {
            if (isFunc(token)) {
                double val;
                val = stod(outStack.popBack());
                outStack.pushBack(to_string(operation(token, val, 0)));
            } else {
                if (outStack.size() < 2)
                    throw "Invalid operation order";
                double left, right;
                right = stod(outStack.popBack());
                left = stod(outStack.popBack());
                outStack.pushBack(to_string(operation(token, left, right)));
            }   
        }
    }
	if (outStack.size() != 1)
		throw "Invalid stack size";
	return stod(outStack.pop());
}

vector<string> tokenize(string text) {
    vector<string> tokens;
    text.erase(std::remove(text.begin(), text.end(), ' '), text.end());

    string current = "";
    for (int i = 0; i < text.size(); i++) {
        current.clear(); // Clear results received before.
        char c = text[i];
        // If character is a digit
        if (isdigit(c)) {
            current += c;
            // Iterate forwards and grab anything that is a digit or delimiter (.)
            for (i++; i < text.size() && (isdigit(text[i]) || text[i] == '.'); i++) current += text[i];
            tokens.push_back(current);
            // Check if next symbol is '(' and add * if needed
            if (i < text.size() && (isalpha(text[i]) || text[i] == '(')) tokens.push_back("*");
            i--;
            continue;
        }
        // Checking characters, if they match some operators
        for (auto& op : OPS_ALL) {
            if (contains(text, op, i)) {
                i += op.size() - 1;
                tokens.push_back(op);
                break;
            }
        }
    }
    return tokens;
}

vector<string> rpn(string& inpt_str) {
    vector<string> result;
    vector<string> str_tokens = tokenize(inpt_str);
    Stack opStack;

    for (string token : str_tokens) {
        if (isNumber(token)) result.push_back(token);
        else if (token == "(") opStack.push(token);
        else if (token == ")") {
            while (opStack.size() && opStack.front() != "(") result.push_back(opStack.pop());
            if (opStack.size() == 0) throw "Unpaired bracket encountered";
            opStack.pop();
        } else if (isOperation(token)) {
            while (opStack.size() && opStack.front() != "(" && shouldMove(token, opStack)) result.push_back(opStack.pop());
            opStack.push(token);
        }
    }

    while (opStack.size()) {
        if (opStack.front() == "(") throw "Unpaired bracket encountered";
        result.push_back(opStack.pop());
    }

    return result;
}

void linkedListMenu() {
    LinkedList ll;
    while (true) {
        system("cls");
        cout << ll << " (size " << ll.size() << ")" << endl;
        cout <<
            "Linked Lists - Choose an action from below:\n"
            "0. Back\n"
            "1. Append element\n"
            "2. Insert element\n"
            "3. Remove element by index\n"
            "4. Remove element by value\n"
            "5. Clear\n"
            "6. Element at\n"
            "7. Search\n"
            "8. Swap by index\n"
            "9. Swap by value\n\n";
        int choice = readValue<int>("Type a number to continue: ");
        cout << endl;
        switch (choice) {
            case 0: return;
            case 1: {
                int v = readValue<int>("Enter integer: ");
                ll.append(v);
                break;
            }
            case 2: {
                int v = readValue<int>("Enter integer: ");
                unsigned i = -1;
                do {
                    i = readValue<unsigned>("Enter index: ");
                } while (i < 0 || i > ll.size());
                ll.insert(i, v);
                break;
            }
            case 3: {
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
            case 4: {
                if (ll.size() == 0) {
                    cout << "Nothing to delete" << endl;
                    break;
                }
                int v = readValue<int>("Enter integer: ");
                ll.remove(v);
                break;
            }
            case 5:
                ll.clear();
                break;
            case 6: {
                int i;
                do {
                    i = readValue<unsigned>("Enter index: ");
                } while (i < 0 || i >= ll.size());
                cout << "Element at " << i << ": " << ll.at(i) << endl;
                break;
            }
            case 7: {
                if (ll.size() == 0) {
                    cout << "Nothing to delete" << endl;
                    break;
                }
                int v = readValue<int>("Enter integer: ");
                cout << "Index is: " << ll.search(v) << endl;
                break;
            }
            case 8: {
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
            case 9: {
                int v1 = readValue<int>("Enter value 1: ");
                int v2;
                do {
                    v2 = readValue<int>("Enter value 2: ");
                } while (v1 == v2);
                ll.swap(v1, v2);
                break;
            }
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
                break;
        }
        system("pause");
    }
}

void dynamicArrayMenu() {
    Vector da;
    while (true) {
        system("cls");
        cout << da << " (size " << da.size() << ", capacity " << da.cap() << ")" << endl;
        cout <<
            "Dynamic Arrays - Choose an action from below:\n"
            "0. Back\n"
            "1. Append element\n"
            "2. Insert element\n"
            "3. Remove element by index\n"
            "4. Remove element by value\n"
            "5. Clear\n"
            "6. Element at\n"
            "7. Search\n"
            "8. Swap by index\n"
            "9. Swap by value\n\n";
        int choice = readValue<int>("Type a number to continue: ");
        cout << endl;
        switch (choice) {
            case 0: return;
            case 1: {
                int v = readValue<int>("Enter integer: ");
                da.append(v);
                break;
            }
            case 2: {
                int v = readValue<int>("Enter integer: ");
                unsigned i = -1;
                do {
                    i = readValue<unsigned>("Enter index: ");
                } while (i < 0 || i > da.size());
                da.insert(i, v);
                break;
            }
            case 3: {
                if (da.size() == 0) {
                    cout << "Nothing to delete" << endl;
                    break;
                }
                unsigned i = -1;
                do {
                    i = readValue<unsigned>("Enter index: ");
                } while (i < 0 || i >= da.size());
                da.remove(i);
                break;
            }
            case 4: {
                if (da.size() == 0) {
                    cout << "Nothing to delete" << endl;
                    break;
                }
                int v = readValue<int>("Enter integer: ");
                da.remove(v);
                break;
            }
            case 5:
                da.clear();
                break;
            case 6: {
                int i;
                do {
                    i = readValue<unsigned>("Enter index: ");
                } while (i < 0 || i >= da.size());
                cout << "Element at " << i << ": " << da.at(i) << endl;
                break;
            }
            case 7: {
                if (da.size() == 0) {
                    cout << "Nothing to get" << endl;
                    break;
                }
                int v = readValue<int>("Enter integer: ");
                cout << "Index is: " << da.search(v) << endl;
                break;
            }
            case 8: {
                unsigned i1, i2;
                do {
                    i1 = readValue<unsigned>("Enter index 1: ");
                } while (i1 < 0 || i1 >= da.size());
                do {
                    i2 = readValue<unsigned>("Enter index 2: ");
                } while (i2 < 0 || i2 >= da.size() || i1 == i2);
                da.swap(i1, i2);
                break;
            }
            case 9: {
                int v1 = readValue<int>("Enter value 1: ");
                int v2;
                do {
                    v2 = readValue<int>("Enter value 2: ");
                } while (v1 == v2);
                da.swap(v1, v2);
                break;
            }
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
                break;
        }
        system("pause");
    }
}


void stackMenu() {
    Stack s;
    while (true) {
        system("cls");
        cout << s << " (size " << s.size() << ")" << endl;
        cout <<
            "Stacks - Choose an action from below:\n"
            "0. Back\n"
            "1. Check front (top)\n"
            "2. Check back (bottom)\n"
            "3. Push element\n"
            "4. Push element to back\n"
            "5. Pop element\n"
            "6. Pop element from back\n"
            "7. Clear\n\n";
        int choice = readValue<int>("Type a number to continue: ");
        cout << endl;
        switch (choice) {
            case 0: return;
            case 1: {
                if (s.size() == 0) {
                    cout << "Stack is empty" << endl;
                    break;
                }
                cout << "Front: " << s.front() << endl;
                break;
            }
            case 2: {
                if (s.size() == 0) {
                    cout << "Stack is empty" << endl;
                    break;
                }
                cout << "Back: " << s.back() << endl;
                break;
            }
            case 3: {
                string v;
                readLine("Enter element: ", &v);
                s.push(v);
                break;
            }
            case 4: {
                string v;
                readLine("Enter element: ", &v);
                s.pushBack(v);
                break;
            }
            case 5: {
                if (s.size() == 0) {
                    cout << "Stack is empty" << endl;
                    break;
                }
                string v = s.pop();
                cout << "Popped: " << v << endl;
                break;
            }
            case 6: {
                if (s.size() == 0) {
                    cout << "Stack is empty" << endl;
                    break;
                }
                string v = s.popBack();
                cout << "Popped: " << v << endl;
                break;
            }
            case 7:
                s.clear();
                break;
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
                break;
        }
        system("pause");
    }
}

void shuntingYardMenu() {
    while (true) {
        string inp;
        readLine("Enter mathematical expression (0 to cancel): ", &inp);
        if (inp == "0") return;
        vector<string> tk = tokenize(inp);
        vector<string> sy = rpn(inp);
        cout << "Tokenized expression: " << vecToString(tk) << endl; 
        cout << "Final expression form: " << vecToString(sy) << endl; 
    }
}

int main() {
    while (true) {
        system("cls");
        cout <<
            "Choose a category from below:\n"
            "0. Exit\n"
            "1. Linked Lists\n"
            "2. Dynamic Arrays\n"
            "3. Stacks\n"
            "4. Shunting Yard\n";
        int choice = readValue<int>("Type a number to continue: ");
        cout << endl;
        switch (choice) {
            case 0:
                return 0;
            case 1:
                linkedListMenu();
                break;
            case 2:
                dynamicArrayMenu();
                break;
            case 3:
                stackMenu();
                break;
            case 4:
                shuntingYardMenu();
                break;
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
                break;
        }
    }
}
// "5**4 + 3sin(12 + 1) + 2(2*4 ^ 7 - 2)"