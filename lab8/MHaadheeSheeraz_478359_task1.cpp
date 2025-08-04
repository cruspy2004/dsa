#include <iostream>
#include <algorithm>
using namespace std;

// Node structure for BST
struct node {
    int data;
    node* left;
    node* right;
};

class BST {
private:
    node* root;

    // Helper function for recursive insert
    void insert(node*& curr, int value) {
        if (curr == nullptr) {
            curr = new node{value, nullptr, nullptr};
            return;
        }
        if (value < curr->data) insert(curr->left, value);
        else if (value > curr->data) insert(curr->right, value);
    }

    // Recursive preorder traversal
    void preOrder(node* curr) {
        if (curr == nullptr) return;
        cout << curr->data << " ";
        preOrder(curr->left);
        preOrder(curr->right);
    }

    // Recursive inorder traversal
    void inOrder(node* curr) {
        if (curr == nullptr) return;
        inOrder(curr->left);
        cout << curr->data << " ";
        inOrder(curr->right);
    }

    // Recursive postorder traversal
    void postOrder(node* curr) {
        if (curr == nullptr) return;
        postOrder(curr->left);
        postOrder(curr->right);
        cout << curr->data << " ";
    }

    // Print only leaf nodes
    void printLeaves(node* curr) {
        if (curr == nullptr) return;
        if (curr->left == nullptr && curr->right == nullptr) {
            cout << curr->data << " ";
            return;
        }
        printLeaves(curr->left);
        printLeaves(curr->right);
    }

    // Count leaf nodes
    int countLeaves(node* curr) {
        if (curr == nullptr) return 0;
        if (curr->left == nullptr && curr->right == nullptr) return 1;
        return countLeaves(curr->left) + countLeaves(curr->right);
    }

    // Count internal (non-leaf) nodes
    int countInternal(node* curr) {
        if (curr == nullptr || (curr->left == nullptr && curr->right == nullptr)) return 0;
        return 1 + countInternal(curr->left) + countInternal(curr->right);
    }

    // Calculate height of the tree
    int height(node* curr) {
        if (curr == nullptr) return -1;
        return 1 + max(height(curr->left), height(curr->right));
    }

    // Recursive helper to print depth of each node
    void depthHelper(node* curr, int level) {
        if (curr == nullptr) return;
        cout << "Node: " << curr->data << " Depth: " << level << endl;
        depthHelper(curr->left, level + 1);
        depthHelper(curr->right, level + 1);
    }

public:
    BST() { root = nullptr; }

    // Check if BST is empty
    bool isEmpty() {
        return root == nullptr;
    }

    // Search function using loc and ploc
    void search(int value, node*& loc, node*& ploc) {
        loc = root;
        ploc = nullptr;

        while (loc != nullptr && loc->data != value) {
            ploc = loc;
            if (value < loc->data) loc = loc->left;
            else loc = loc->right;
        }
    }

    // Insert value only if it's not a duplicate
    void insertWithoutDuplication(int value) {
        node* loc;
        node* ploc;
        search(value, loc, ploc);

        if (loc != nullptr) {
            cout << "Value already exists: " << value << endl;
            return;
        }

        node* newNode = new node{value, nullptr, nullptr};

        if (ploc == nullptr) {
            root = newNode;
            cout << "Inserted as root: " << value << endl;
        } else if (value < ploc->data) {
            ploc->left = newNode;
            cout << "Inserted to left of: " << ploc->data << endl;
        } else {
            ploc->right = newNode;
            cout << "Inserted to right of: " << ploc->data << endl;
        }
    }

    void preOrderTraversal() {
        preOrder(root);
        cout << endl;
    }

    void inOrderTraversal() {
        inOrder(root);
        cout << endl;
    }

    void postOrderTraversal() {
        postOrder(root);
        cout << endl;
    }

    // Print minimum value in BST
    void printMin() {
        if (isEmpty()) {
            cout << "Tree is empty." << endl;
            return;
        }
        node* curr = root;
        while (curr->left != nullptr)
            curr = curr->left;
        cout << "Smallest value: " << curr->data << endl;
    }

    // Print maximum value in BST
    void printMax() {
        if (isEmpty()) {
            cout << "Tree is empty." << endl;
            return;
        }
        node* curr = root;
        while (curr->right != nullptr)
            curr = curr->right;
        cout << "Largest value: " << curr->data << endl;
    }

    void printLeafNodes() {
        printLeaves(root);
        cout << endl;
    }

    int countLeafNodes() {
        return countLeaves(root);
    }

    int countInternalNodes() {
        return countInternal(root);
    }

    int calculateHeight() {
        return height(root);
    }

    void calculateDepth() {
        depthHelper(root, 0);
    }
};

// Example usage:
int main() {
    BST tree;
    tree.insertWithoutDuplication(50);
    tree.insertWithoutDuplication(30);
    tree.insertWithoutDuplication(70);
    tree.insertWithoutDuplication(20);
    tree.insertWithoutDuplication(40);
    tree.insertWithoutDuplication(60);
    tree.insertWithoutDuplication(80);

    cout << "Inorder: "; tree.inOrderTraversal();
    cout << "Preorder: "; tree.preOrderTraversal();
    cout << "Postorder: "; tree.postOrderTraversal();

    tree.printMin();
    tree.printMax();

    cout << "Leaf nodes: "; tree.printLeafNodes();
    cout << "Leaf count: " << tree.countLeafNodes() << endl;
    cout << "Internal nodes count: " << tree.countInternalNodes() << endl;
    cout << "Height: " << tree.calculateHeight() << endl;

    cout << "Node depths: " << endl;
    tree.calculateDepth();

    return 0;
}
