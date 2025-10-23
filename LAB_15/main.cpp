#include <iostream>
#include <string>
#include <vector>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int value): data(value), left(nullptr), right(nullptr) {}
};
Node* treeString(const std::string& s, size_t& pos) {
    while (pos < s.length() && s[pos] == ' ') {
        pos++;
    }
    if (pos >= s.length()) {
        return nullptr;
    }
    if (isdigit(s[pos])) {
        std::string numStr;
        while (pos < s.length() && isdigit(s[pos])) {
            numStr += s[pos];
            pos++;
        }
        Node* node = new Node(std::stoi(numStr));
        while (pos < s.length() && s[pos] == ' ') {
            pos++;
        }
        if (pos < s.length() && s[pos] == '(') {
            pos++;
            node->left = treeString(s, pos);
            while (pos < s.length() && s[pos] == ' ') {
                pos++;
            }
            if (pos < s.length() && s[pos] == ',') {
                pos++;
            }
            node->right = treeString(s, pos);
            while (pos < s.length() && s[pos] == ' ') {
                pos++;
            }
            if (pos < s.length() && s[pos] == ')') {
                pos++;
            }
        }
        return node;
    }
    else if (pos < s.length() && s[pos] == ',') {
        pos++;
        return nullptr;
    }
    return nullptr;
}
// Прямой обход (pre-order)
void preOrder(Node* root, std::vector<int>& result) {
    if (root == nullptr) { return; }
    result.push_back(root->data);
    preOrder(root->left, result);
    preOrder(root->right, result);
}
// Центральный обход (in-order)
void inOrder(Node* root, std::vector<int>& result) {
    if (root == nullptr) { return; }
    inOrder(root->left, result);
    result.push_back(root->data);
    inOrder(root->right, result);
}
// Концевой обход (post-order)
void postOrder(Node* root, std::vector<int>& result) {
    if (root == nullptr) { return; }
    postOrder(root->left, result);
    postOrder(root->right, result);
    result.push_back(root->data);
}
// Функция для освобождения памяти
void freeTree(Node* root) {
    if (root == nullptr) { return; }
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}
void print(std::vector<int>& result) {
    for (size_t i = 0; i < result.size(); i++) {
        std::cout << result[i];
        if (i < result.size() - 1) { std::cout << " "; }
    }
    std::cout << std::endl;
}
int main() {
    std::string input_str;
    getline(std::cin, input_str);
    size_t pos = 0;
    Node* root = treeString(input_str, pos);
    std::vector<int> result;
    preOrder(root, result);
    std::cout << "pre-order: ";
    print(result);
    result.clear();
    inOrder(root, result);
    std::cout << "in-order: ";
    print(result);
    result.clear();
    postOrder(root, result);
    std::cout << "post-order: ";
    print(result);
    freeTree(root);
    
    return 0;
}