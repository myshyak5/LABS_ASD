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
    while (pos < s.length() && s[pos] == ' ') { pos++; }
    if (pos >= s.length()) { return nullptr; }
    if (isdigit(s[pos])) {
        std::string numStr;
        while (pos < s.length() && isdigit(s[pos])) {
            numStr += s[pos];
            pos++;
        }
        Node* node = new Node(std::stoi(numStr));
        while (pos < s.length() && s[pos] == ' ') { pos++; }
        if (pos < s.length() && s[pos] == '(') {
            pos++;
            node->left = treeString(s, pos);
            while (pos < s.length() && s[pos] == ' ') { pos++; }
            if (pos < s.length() && s[pos] == ',') { pos++; }
            node->right = treeString(s, pos);
            while (pos < s.length() && s[pos] == ' ') { pos++;}
            if (pos < s.length() && s[pos] == ')') { pos++; }
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
    std::vector<Node*> stack;
    stack.push_back(root);
    while (!stack.empty()) {
        Node* current = stack.back();
        stack.pop_back();
        result.push_back(current->data);
        if (current->right != nullptr) { stack.push_back(current->right); }
        if (current->left != nullptr) { stack.push_back(current->left); }
    }
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
    freeTree(root);
    
    return 0;
}