#include <iostream>
#include <string>
#include <vector>

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
};

class Tree {
    TreeNode* root;

    void destroy(TreeNode* node);
    void walk(TreeNode* node, std::vector<int>& vec);
    void print(TreeNode* node, const std::string& rpf = "", const std::string& mpf = "", const std::string& lpf = "");
public:
    Tree(int rootv = 0);
    Tree(std::string s);
    ~Tree();

    void destroy();
    std::vector<int> walk();
    friend std::ostream& operator<<(std::ostream&, Tree&);
};