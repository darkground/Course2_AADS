#include "tree.h"

enum ParseState {
    VALUE = 0,
    LBRANCH = 1,
    RBRANCH = 2,
    END = 3
};

size_t parse(std::string s, TreeNode*& nd, size_t pos = 1) {
    ParseState state = ParseState::VALUE;
    for (size_t i = pos; i < s.length(); i++) {
        char c = s[i];
        if (c == '(') {
            switch (state) {
            case ParseState::END:
            case ParseState::VALUE:
                throw std::runtime_error("Unexpected opening bracket at pos " + std::to_string(i + 1));
            case ParseState::LBRANCH: {
                nd->left = new TreeNode();
                i = parse(s, nd->left, ++i);
                state = ParseState::RBRANCH;
                break;
            }
            case ParseState::RBRANCH: {
                nd->right = new TreeNode();
                i = parse(s, nd->right, ++i);
                state = ParseState::END;
                break;
            }
            }
        }
        else if (c == ')') {
            if (state == ParseState::VALUE) throw std::runtime_error("Unexpected closing bracket at pos " + std::to_string(i + 1));
            return i;
        }
        else if (c == 'n') {
            if (state != ParseState::VALUE) throw std::runtime_error("Unexpected value at pos " + std::to_string(i + 1));
            if ((i < s.length() - 2) && s[i + 1] == 'i' && s[i + 2] == 'l') {
                delete nd;
                nd = 0;
                i += 2;
                state = ParseState::END;
            }
            else throw std::runtime_error("Unexpected symbol at pos " + std::to_string(i + 1));
        }
        else if (isdigit(c)) {
            if (state != ParseState::VALUE) throw std::runtime_error("Unexpected value at pos " + std::to_string(i + 1));
            std::string acc;
            for (; s[i] && isdigit(s[i]); i++)
                acc.push_back(s[i]);
            nd->value = stoi(acc);
            i--;
            state = ParseState::LBRANCH;
        }
        else if (c == ' ') continue;
        else throw std::runtime_error("Unexpected symbol at pos " + std::to_string(i + 1));
    }
    return s.length() - 1;
}

Tree::Tree(int rootv) {
    root = new TreeNode;
    root->left = NULL;
    root->right = NULL;
    root->value = rootv;
}

Tree::Tree(std::string s) : Tree(0) {
    parse(s, root);
}

Tree::~Tree() {
    destroy();
}

void Tree::destroy(TreeNode* node) {
    if (node != 0) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

void Tree::print(std::ostream& os, TreeNode* root, const std::string& rpf, const std::string& mpf, const std::string& lpf) {
    if (root != NULL) {
        if (root->right)
            print(os, root->right, rpf + "   ", rpf + ".-->", rpf + "|  ");
        os << mpf << root->value << std::endl;
        if (root->left)
            print(os, root->left, lpf + "|  ", lpf + "`-->", lpf + "   ");
    }
}

void Tree::destroy() {
    destroy(root);
    root = NULL;
}

void Tree::walk(TreeNode* node, std::vector<int>& vec) {
    if (node) {
        vec.push_back(node->value);
        walk(node->left, vec);
        walk(node->right, vec);
    }
}

std::vector<int> Tree::walk() {
    std::vector<int> vec;
    walk(root, vec);
    return vec;
}

std::ostream& operator<<(std::ostream& os, Tree& t) {
    t.print(os, t.root);
    return os;
}