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
            while (pos < s.length() && s[pos] == ' ') { pos++; }
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
Node* search(Node* root, int value) {
    if (root == nullptr || root->data == value) { return root; }
    if (value < root->data) { return search(root->left, value); }
    else { return search(root->right, value); }
}
Node* insert(Node* root, int value) {
    if (root == nullptr) { return new Node(value); }
    if (value < root->data) { root->left = insert(root->left, value); }
    else if (value > root->data) { root->right = insert(root->right, value); }
    return root;
}
Node* findMin(Node* root) {
    while (root && root->left != nullptr) { root = root->left; }
    return root;
}
Node* remove(Node* root, int value) {
    if (root == nullptr) { return root; }
    if (value < root->data) { root->left = remove(root->left, value); }
    else if (value > root->data) { root->right = remove(root->right, value); }
    else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = remove(root->right, temp->data);
    }
    return root;
}
// Функция для освобождения памяти
void freeTree(Node* root) {
    if (root == nullptr) { return; }
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}
std::string treeToString(Node* root) {
    if (root == nullptr) { return ""; }
    std::string result = std::to_string(root->data);
    if (root->left != nullptr || root->right != nullptr) {
        result += "(" + treeToString(root->left) + "," + treeToString(root->right) + ")";
    }
    return result;
}
int main() {
    std::string input_str;
    getline(std::cin, input_str);
    size_t pos = 0;
    Node* root = treeString(input_str, pos);
    std::cout << "MENU:\nsearch - 1\ninsert - 2\nremove - 3\nexit - 0" << std::endl;
    int choice;
    do {
        std::cin >> choice;
        switch (choice) {
            case 1: {
                int value;
                std::cin >> value;
                Node* found = search(root, value);
                if (found != nullptr) { std::cout << value << " found" << std::endl; }
                else { std::cout << value << " not found" << std::endl; }
                std::cout << "MENU:\nsearch - 1\ninsert - 2\nremove - 3\nexit - 0" << std::endl;
                break;
            }
            case 2: {
                int value;
                std::cin >> value;
                if (search(root, value) == nullptr) {
                    root = insert(root, value);
                    std::cout << value << " inserted" << std::endl;
                }
                else { std::cout << value << " already exists" << std::endl; }
                std::cout << "MENU:\nsearch - 1\ninsert - 2\nremove - 3\nexit - 0" << std::endl;
                break;
            }
            case 3: {
                int value;
                std::cin >> value;
                Node* found = search(root, value);
                if (found != nullptr) {
                    root = remove(root, value);
                    std::cout << value << " deleted" << std::endl;
                }
                else { std::cout << value << " not found" << std::endl; }
                std::cout << "MENU:\nsearch - 1\ninsert - 2\nremove - 3\nexit - 0" << std::endl;
                break;
            }
            case 0: break;  
            default: continue;
        }
    } while (choice != 0);
    std::cout << treeToString(root) << std::endl;
    freeTree(root);
    return 0;
}