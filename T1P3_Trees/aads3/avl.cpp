#include "avl.h"

enum ParseState {
    VALUE = 0,
    LBRANCH = 1,
    RBRANCH = 2,
    END = 3
};

size_t parse(std::string s, TreeAVLNode*& nd, size_t pos = 1) {
    ParseState state = ParseState::VALUE;
    for (size_t i = pos; s[i]; i++) {
        char c = s[i];
        if (c == '(') {
            switch (state) {
            case ParseState::END:
            case ParseState::VALUE:
                throw std::runtime_error("Unexpected opening bracket");
            case ParseState::LBRANCH: {
                nd->left = new TreeAVLNode();
                i = parse(s, nd->left, ++i);
                state = ParseState::RBRANCH;
                break;
            }
            case ParseState::RBRANCH: {
                nd->right = new TreeAVLNode();
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
            if (nd == 0) {
                nd = new TreeAVLNode;
                nd->left = NULL;
                nd->right = NULL;
            }
            nd->value = stoi(acc);
            i--;
            state = ParseState::LBRANCH;
        }
        else if (c == ' ') continue;
        else throw std::runtime_error("Unexpected symbol");
    }
    return s.length() - 1;
}

// Создать АВЛ-дерево
TreeAVL::TreeAVL(int rootv) {
    root = new TreeAVLNode;
	root->left = NULL;
    root->right = NULL;
	root->value = rootv;
    root->height = 0;
}

TreeAVL::TreeAVL(std::string s) {
    parse(s, root);
}

TreeAVL::TreeAVL(std::vector<int> v) {
    for (int i : v)
        add(i);
}

TreeAVL::~TreeAVL() {
    destroy();
}

// Минимальный элемент в АВЛ-дереве 
TreeAVLNode* TreeAVL::min(TreeAVLNode* nd) {
	while (nd->left)
		nd = nd->left;
	return nd;
}

// Максимальный элемент в АВЛ-дереве
TreeAVLNode* TreeAVL::max(TreeAVLNode* nd) {
	while (nd->right)
		nd = nd->right;
	return nd;
}

TreeAVLNode* TreeAVL::min() {
	return min(root);
}

TreeAVLNode* TreeAVL::max() {
	return max(root);
}

// Размер АВЛ-дерева
unsigned TreeAVL::size(TreeAVLNode* root, unsigned size_count) {
	if (root) {
		size_count++;
        return size(root->left) + size(root->right);
	} else
        return size_count;
}

unsigned TreeAVL::size() {
    return size(root, 0);
}

// Вывод бинарного дерева
void TreeAVL::print(TreeAVLNode* root, const std::string& rpf, const std::string& mpf, const std::string& lpf) {
	if (root != NULL) {
        if (root->right)
            print(root->right, rpf + "   ", rpf + ".-->", rpf + "|  ");
        std::cout << mpf << root->value << std::endl;
        if (root->left)
            print(root->left, lpf + "|  ", lpf + "`-->", lpf + "   ");
    }
}

// Поиск в АВЛ-дереве значения
TreeAVLNode* TreeAVL::search(int value, TreeAVLNode* root) {
    if (root != nullptr) {
        if (value == root->value)
            return root;
        if (value < root->value)
            return search(value, root->left);
        else
            return search(value, root->right);
    } else return NULL;
}

TreeAVLNode* TreeAVL::search(int value) {
    return search(value, root);
}

// Удаление элемента из АВЛ-дерева
TreeAVLNode* TreeAVL::remove(int value, TreeAVLNode* root) {
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
            TreeAVLNode* minnode = min(root->right);
            root->value = minnode->value;
            root->right = remove(minnode->value, root->right);
        }
	}

    return root ? balance(root) : NULL;
}

TreeAVLNode* TreeAVL::remove(int value) {
    return remove(value, root);
}

// Добавить значение в АВЛ-дерево
void TreeAVL::add(int value) {
    if (root == NULL) {
        root = new TreeAVLNode;
        root->left = NULL;
        root->right = NULL;
        root->value = value;
        root->height = 0;
    } else root = insert(value, root);
}

// Добавить значение в АВЛ-дерево (root != null)
TreeAVLNode* TreeAVL::insert(int value, TreeAVLNode* root) {
	if(!root) {
        root = new TreeAVLNode;
        root->value = value;
        root->height = 1;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
	if(value < root->value)
		root->left = insert(value, root->left);
	else if (value > root->value)
		root->right = insert(value, root->right);
	return balance(root);
}

TreeAVLNode* TreeAVL::insert(int value) {
    return insert(value, root);
}

// Уничтожить АВЛ-дерево
void TreeAVL::destroy(TreeAVLNode* root) {
    if(root!=NULL) {
        destroy(root->left);
        destroy(root->right);
        delete root;
    }
}

void TreeAVL::destroy() {
    destroy(root);
    root = NULL;
}

// Straight-walk: Прямой обход АВЛ-дерева
void TreeAVL::strw(TreeAVLNode* node, std::vector<int>& vec) {
    if(node){
        vec.push_back(node->value);
        strw(node->left, vec);
        strw(node->right, vec);
    }
}

// Reverse-walk: Обратный обход АВЛ-дерева
void TreeAVL::revw(TreeAVLNode* node, std::vector<int>& vec) {
    if(node){
        revw(node->left, vec);
        revw(node->right, vec);
        vec.push_back(node->value);
    }
}

// Symmetrical-walk: Симметричный обход АВЛ-дерева
void TreeAVL::symw(TreeAVLNode* node, std::vector<int>& vec) {
    if(node){
        symw(node->left, vec);
        vec.push_back(node->value);
        symw(node->right, vec);
    }
}

std::vector<int> TreeAVL::strw() {
    std::vector<int> vec;
    strw(root, vec);
    return vec;
}

std::vector<int> TreeAVL::revw() {
    std::vector<int> vec;
    revw(root, vec);
    return vec;
}

std::vector<int> TreeAVL::symw() {
    std::vector<int> vec;
    symw(root, vec);
    return vec;
}

// Малое правое вращение
TreeAVLNode* TreeAVL::rotright(TreeAVLNode* node)
{
    TreeAVLNode* ltree = node->left;
    TreeAVLNode* subtree = ltree->right;

    ltree->right = node;
    node->left = subtree;

    node->recalcHeight();
    ltree->recalcHeight();

    return ltree;
}

// Малое левое вращение
TreeAVLNode* TreeAVL::rotleft(TreeAVLNode* node)
{
    TreeAVLNode* rtree = node->right;
    TreeAVLNode* subtree = rtree->left;
 
    rtree->left = node;
    node->right = subtree;
 
    node->recalcHeight();
    rtree->recalcHeight();

    return rtree;
}

// Сбалансировать узел
TreeAVLNode* TreeAVL::balance(TreeAVLNode* node) {
	node->recalcHeight();

	if(TreeAVLNode::bfactor(node) == 2) {
		if(TreeAVLNode::bfactor(node->right) < 0)
			node->right = rotright(node->right);
		return rotleft(node);
	}
	if(TreeAVLNode::bfactor(node) == -2) {
		if(TreeAVLNode::bfactor(node->left) > 0)
			node->left = rotleft(node->left);
		return rotright(node);
	}

	return node; 
}

std::ostream& operator<<(std::ostream& os, TreeAVL& avl) {
    avl.print(avl.root);
	return os;
}