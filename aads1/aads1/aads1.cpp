﻿#include <iostream>
#include <vector>
#include <map>
#include "list.h"
#include "vector.h"
#include "stack.h"
#include <unordered_map>

using namespace std;

const string OPS_ALL[] = {
    "**", "//",
    "*", "/", "-", "+", "^",
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
    {"//", 2}, //same as /
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
    while (it != str.end() && isdigit(*it)) ++it;
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

int main()
{
    string ex = "5**4 + 3sin(12 + 1) + 2(2*4 ^ 7 - 2)";
    cout << "example: " << ex << endl;
    cout << "result: " << vecToString(rpn(ex)) << endl;
    while (true) {
        string i;
        getline(cin, i);
        cout << "result: " << vecToString(rpn(i)) << endl;
    }
}