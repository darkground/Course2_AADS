#pragma once
#include <string>
#include <ostream>
#include <vector>
#include <queue>
#include <stack>

struct TreeBinaryNode {
    int value;
    TreeBinaryNode* left;
    TreeBinaryNode* right;
};

class TreeBinary {
    TreeBinaryNode* root;

    TreeBinaryNode* remove(int key, TreeBinaryNode* node);
    TreeBinaryNode* min(TreeBinaryNode* node);
    TreeBinaryNode* max(TreeBinaryNode* node);
    TreeBinaryNode* search(int key, TreeBinaryNode* node);
    unsigned size(TreeBinaryNode* node, unsigned size_count = 0);
    void insert(int key, TreeBinaryNode* node);
    void destroy(TreeBinaryNode* node);
    void print(std::ostream& os, TreeBinaryNode* node, const std::string& rpf = "", const std::string& mpf = "", const std::string& lpf = "");
public:
    TreeBinary(int rootv = 0);
    TreeBinary(std::string s);
    TreeBinary(std::vector<int> v);
    ~TreeBinary();

    TreeBinaryNode* min();
    TreeBinaryNode* max();
    TreeBinaryNode* search(int key);
    TreeBinaryNode* remove(int key);
    void insert(int key);
    void add(int value);
    unsigned size();
    void destroy();

    std::vector<int> widew();
    std::vector<int> strw();
    std::vector<int> revw();
    std::vector<int> symw();

    friend std::ostream& operator<<(std::ostream&, TreeBinary&);
};