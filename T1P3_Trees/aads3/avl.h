#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>

struct TreeAVLNode {
    int height;
    int value;
    TreeAVLNode* left;
    TreeAVLNode* right;

    // Получить высоту АВЛ-узла (если узел == null, высота равна 0)
    static int getHeight(TreeAVLNode* node) {
        return node == NULL ? 0 : node->height;
    }

    // Получить фактор сбалансированности АВЛ-узла (если узел == null, фактор равен 0)
    static int bfactor(TreeAVLNode* node) {
        return node == NULL ? 0 : (getHeight(node->right) - getHeight(node->left));
    }

    // Пересчитать высоту АВЛ-узла и записать в node->height
    void recalcHeight() {
        int hl = getHeight(left);
        int hr = getHeight(right);
        height = (hl>hr ? hl : hr) + 1;
    }
};

class TreeAVL {
    TreeAVLNode* root;

    TreeAVLNode* remove(int key, TreeAVLNode* node);
    TreeAVLNode* min(TreeAVLNode* node);
    TreeAVLNode* max(TreeAVLNode* node);
    TreeAVLNode* search(int key, TreeAVLNode* node);
    unsigned size(TreeAVLNode* node, unsigned size_count = 0);
    TreeAVLNode* insert(int key, TreeAVLNode* node);
    void destroy(TreeAVLNode* node);
    void print(TreeAVLNode* node, const std::string& rpf = "", const std::string& mpf = "", const std::string& lpf = "");
    void strw(TreeAVLNode* root, std::vector<int>& vec);
    void revw(TreeAVLNode* root, std::vector<int>& vec);
    void symw(TreeAVLNode* root, std::vector<int>& vec);
public:
    TreeAVL(int rootv = 0);
    TreeAVL(std::string s);
    TreeAVL(std::vector<int> v);
    ~TreeAVL();

    TreeAVLNode* min();
    TreeAVLNode* max();
    TreeAVLNode* search(int key);
    TreeAVLNode* remove(int key);
    TreeAVLNode* insert(int key);
    void add(int value);
    unsigned size();
    void destroy();

    std::vector<int> widew();
    std::vector<int> strw();
    std::vector<int> revw();
    std::vector<int> symw();

    TreeAVLNode* rotright(TreeAVLNode* p);
    TreeAVLNode* rotleft(TreeAVLNode* q);
    TreeAVLNode* balance(TreeAVLNode* p);

    friend std::ostream& operator<<(std::ostream&, TreeAVL&);
};