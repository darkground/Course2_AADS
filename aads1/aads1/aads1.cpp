#include <iostream>
#include <sstream>
#include <vector>
#include "list.h"
#include "vector.h"
#include "stack.h"

using namespace std;

const string OPS_FUNC[] = {
    "sin", "cos", "tan", "cot",
    "sinh", "cosh", "tanh", "coth",
};

const string OPS_NONFUNC[] = {
    "**", "//", "++", "--",
    "*", "/", "-", "+", "^",
    "(", ")"
};


vector<string> tokenize(string text) {
    vector<string> tokens;
    string current = "";
    for (int i = 0; i < text.size(); i++) {
        current.clear();
        char c = text[i];
        if (c == '-' && i + 1 < text.size() && isdigit(text[i + 1])) {
            current += c;
            c = text[++i];
        }
        if (isdigit(c)) {
            current += c;
            int j = i + 1;
            for (; j < text.size(); j++) {
                if (isdigit(text[j]) || text[j] == '.')
                    current += text[j];
                else break;
            }
            i = j - 1;
            if (current.size() > 0) tokens.push_back(current);
            continue;
        }
        if (isalpha(c)) {
            current += c;
            int j = i + 1;
            for (; j < text.size(); j++) {
                if (isalpha(text[j])) current += text[j];
                else break;
            }
            bool is_func = find(begin(OPS_FUNC), end(OPS_FUNC), current) != end(OPS_FUNC);
            if (is_func) {
                if (j < text.size() && text[j] == '(') {
                    current += text[j++];
                    tokens.push_back(current);
                }
            } else if (current.size() > 0) tokens.push_back(current);
            i = j - 1;
            continue;
        }
        for (auto& op : OPS_NONFUNC) {
            bool match = true;
            int m = 0;
            for (; m < text.size() && m < op.size(); m++) {
                if (text[i + m] != op[m]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                i += m - 1;
                tokens.push_back(op);
                break;
            }
        }
    }
    return tokens;
}

int main()
{
    cout << "example: a**b + 3sin(-10) + a(2*b ^ c - 2)" << endl;
    auto x = tokenize("a**b + 3sin(-10) + a(2*b ^ c - 2)");
    for (auto& v : x)
        cout << "token: " << v << endl;
    while (true) {
        string i;
        getline(cin, i);
        auto x = tokenize(i);
        for (auto& v : x)
            cout << "token: " << v << endl;
    }
}