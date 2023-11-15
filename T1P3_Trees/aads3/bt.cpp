#include "bt.h"

enum ParseState {
    VALUE = 0,
    LBRANCH = 1,
    RBRANCH = 2,
    END = 3
};

size_t parse(std::string s, TreeBinaryNode*& nd, size_t pos = 1) {
    ParseState state = ParseState::VALUE;
    for (size_t i = pos; s[i]; i++) {
        char c = s[i];
        if (c == '(') {
            switch (state) {
            case ParseState::END:
            case ParseState::VALUE:
                throw std::runtime_error("Unexpected opening bracket");
            case ParseState::LBRANCH: {
                nd->left = new TreeBinaryNode();
                i = parse(s, nd->left, ++i);
                state = ParseState::RBRANCH;
                break;
            }
            case ParseState::RBRANCH: {
                nd->right = new TreeBinaryNode();
                i = parse(s, nd->right, ++i);
                state = ParseState::END;
                break;
            }
            }
        }
        else if (c == ')') {
            if (state == ParseState::VALUE) throw std::runtime_error("Unexpected closing bracket");
            return i;
        }
        else if (c == 'n') {
            if (state != ParseState::VALUE) throw std::runtime_error("Unexpected value");
            if ((i < s.length() - 2) && s[i + 1] == 'i' && s[i + 2] == 'l') {
                delete nd;
                nd = 0;
                i += 2;
                state = ParseState::END;
            }
            else throw std::runtime_error("Unexpected symbol");
        }
        else if (isdigit(c)) {
            if (state != ParseState::VALUE) throw std::runtime_error("Unexpected value");
            std::string acc;
            for (; s[i] && isdigit(s[i]); i++)
                acc.push_back(s[i]);
            nd->value = stoi(acc);
            i--;
            state = ParseState::LBRANCH;
        }
        else if (c == ' ') continue;
        else throw std::runtime_error("Unexpected symbol");
    }
    return s.length() - 1;
}

// Создать бинарное дерево
TreeBinary::TreeBinary(int rootv) {
    height = 0; //unused
    sz = 0; //unused
    root = new TreeBinaryNode;
	root->left = NULL;
    root->right = NULL;
	root->value = rootv;
}

TreeBinary::TreeBinary(std::string s) : TreeBinary(0) {
    parse(s, root);
}

TreeBinary::~TreeBinary() {
    destroy();
}

// Минимальный элемент в бинарном дереве 
TreeBinaryNode* TreeBinary::min(TreeBinaryNode* nd) {
	while (nd->left)
		nd = nd->left;
	return nd;
}

// Максимальный элемент в бинарном дереве
TreeBinaryNode* TreeBinary::max(TreeBinaryNode* nd) {
	while (nd->right)
		nd = nd->right;
	return nd;
}

// Минимальный элемент в бинарном дереве 
TreeBinaryNode* TreeBinary::min() {
    return min(root);
}

// Максимальный элемент в бинарном дереве
TreeBinaryNode* TreeBinary::max() {
    return max(root);
}

// Размер бинарного дерева
unsigned TreeBinary::size(TreeBinaryNode* node, unsigned size_count) {
	if (node) {
		size_count++;
        return size(node->left) + size(node->right);
	} else
        return size_count;
}

unsigned TreeBinary::size() {
    return size(root, 0);
}

// Вывод бинарного дерева
void TreeBinary::print(TreeBinaryNode* root, const std::string& rpf, const std::string& mpf, const std::string& lpf) {
	if (root != NULL) {
        if (root->right)
            print(root->right, rpf + "   ", rpf + ".-->", rpf + "|  ");
        std::cout << mpf << root->value << std::endl;
        if (root->left)
            print(root->left, lpf + "|  ", lpf + "`-->", lpf + "   ");
    }
}

// Поиск в бинарном дереве значения
TreeBinaryNode* TreeBinary::search(int value, TreeBinaryNode* root) {
    if (root != nullptr)
    {
        if (value == root->value)
            return root;
        if (value < root->value)
            return search(value, root->left);
        else
            return search(value, root->right);
    }
    else return NULL;
}

TreeBinaryNode* TreeBinary::search(int value) {
    return search(value, root);
}

// Удаление элемента из бинарного дерева
TreeBinaryNode* TreeBinary::remove(int value, TreeBinaryNode* root) {
    if (root == NULL)
        return NULL;
 
    if (value < root->value)
        root->left = remove(value, root->left);
    else if (value > root->value)
        root->right = remove(value, root->right);
    else {
        if (root->left == NULL && root->right == NULL)
            root = NULL;
        else if (root->left == NULL || root->right == NULL)
            root = root->left ? root->left : root->right;
        else {
            TreeBinaryNode* minnode = min(root->right);
            root->value = minnode->value;
            root->right = remove(minnode->value, root->right);
        }
    }

    return root;
}

TreeBinaryNode* TreeBinary::remove(int value) {
    return remove(value, root);
}

// Добавить значение в бинарное дерево
void TreeBinary::add(int value) {
    if (root == NULL) {
        root = new TreeBinaryNode;
        root->left = NULL;
        root->right = NULL;
        root->value = value;
    } else insert(value, root);
}

// Добавить значение в бинарное дерево (root != null)
void TreeBinary::insert(int value, TreeBinaryNode* root) {
    if (!root) return;                            
    if (value < root->value)
    {
        if (root->left != NULL)
            insert(value, root->left);
        else {
            root->left = new TreeBinaryNode;
            root->left->value = value;
            root->left->left = NULL;
            root->left->right = NULL;
        }
    } else if (value >= root->value) {
        if (root->right != NULL)
            insert(value, root->right);
        else {
            root->right = new TreeBinaryNode;
            root->right->value = value;
            root->right->left = NULL;
            root->right->right = NULL;
        }
    }
}

void TreeBinary::insert(int value) {
    insert(value, root);
}

void TreeBinary::destroy(TreeBinaryNode* node) {
    if(node != 0) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

// Уничтожить бинарное дерево
void TreeBinary::destroy() {
    destroy(root);
    root = NULL;
}

// Straight-walk: Прямой обход бинарного дерева
void TreeBinary::strw(TreeBinaryNode* node) {
    if(node){
        std::cout << node->value << ' ';
        strw(node->left);
        strw(node->right);
    }
}

// Reverse-walk: Обратный обход бинарного дерева
void TreeBinary::revw(TreeBinaryNode* node) {
    if(node){
        revw(node->left);
        revw(node->right);
        std::cout << node->value << ' ';
    }
}

// Symmetrical-walk: Симметричный обход бинарного дерева
void TreeBinary::symw(TreeBinaryNode* node) {
    if(node){
        symw(node->left);
        std::cout << node->value << ' ';
        symw(node->right);
    }
}

void TreeBinary::strw() {
    return strw(root);
}

void TreeBinary::revw() {
    return revw(root);
}

void TreeBinary::symw() {
    return symw(root);
}

std::ostream& operator<<(std::ostream& os, TreeBinary& bt) {
    bt.print(bt.root);
	return os;
}