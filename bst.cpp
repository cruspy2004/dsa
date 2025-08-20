#include <iostream>
using namespace std;


struct Node{
    int data; 
    Node* left ; 
    Node* right;

    Node(int value ) : data(value), left(nullptr), right(nullptr) {};
};

class BST {
private:
    Node* root;

public:
    BST() : root(nullptr) {}

    // Recursive function to insert a value into the BST
    Node* insert(Node* root,  int value) {
        if (root == nullptr) {
            return new Node(value);
        }
        if (value < root->data) {
            root->left = insert(root->left, value);
        } else if (value > root->data) {
            root->right = insert(root->right, value);
        }
        return root;
    }
};


int main () {
    BST tree;
    int value;

    cout << "Enter values to insert into the BST (enter -1 to stop):" << endl;
    while (true) {
        cin >> value;
        if (value == -1) break;
        tree.insert(value);
    }

    cout << "Values inserted into the BST." << endl;

    return 0;
}