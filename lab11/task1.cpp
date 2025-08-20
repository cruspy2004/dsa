#include <iostream>
using namespace std;

// Node structure
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int val) : key(val), left(NULL), right(NULL), height(1) {}
};

// Utility to get height
int getHeight(Node* node) {
    return node ? node->height : 0;
}

// Utility to get balance factor
int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Update height of a node
void updateHeight(Node* node) {
    if (node)
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

// Right Rotation (LL Case)
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    cout << "Right Rotation performed on node " << y->key << "\n";
    return x;
}

// Left Rotation (RR Case)
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    cout << "Left Rotation performed on node " << x->key << "\n";
    return y;
}

// Insert into AVL Tree and return new root
Node* insert(Node* node, int key) {
    if (!node) return new Node(key);

    // Basic BST Insertion
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else {
        cout << "Duplicate key " << key << " ignored.\n";
        return node; // duplicate keys not allowed
    }

    // Update height and balance
    updateHeight(node);
    int balance = getBalance(node);

    // Case 1: LL
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Case 2: RR
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Case 3: LR
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Case 4: RL
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Pre-order traversal for tree structure output
void preOrder(Node* root) {
    if (root) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Utility to find the node with the smallest key
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Delete a node from AVL Tree
Node* deleteNode(Node* root, int key) {
    if (!root) return root;

    // Step 1: Normal BST deletion
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node found
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;

            if (!temp) { // No child
                temp = root;
                root = NULL;
            } else { // One child
                *root = *temp;
            }
            delete temp;
        } else {
            // Two children: Get inorder successor
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If tree had only one node
    if (!root) return root;

    // Step 2: Update height
    updateHeight(root);

    // Step 3: Check balance
    int balance = getBalance(root);

    // Step 4: Balance the tree
    // LL
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // LR
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // RL
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


// Run and test insertions
int main() {
    Node* root = NULL;
    int values[] = { 10, 20, 30, 40, 50, 25 };

    cout << "AVL Tree Insertions and Rotations:\n";

    for (int i = 0; i < 6; i++) {
        cout << "\nInserting " << values[i] << ":\n";
        root = insert(root, values[i]);

        cout << "Pre-order Traversal after insertion: ";
        preOrder(root);
        cout << "\n";

            cout << "\nDeleting 40:\n";


        root = deleteNode(root, 40);
        cout << "Pre-order after deletion: ";
        preOrder(root);
        cout << "\n";

        cout << "\nDeleting 30:\n";
        root = deleteNode(root, 30);
        cout << "Pre-order after deletion: ";
        preOrder(root);
        cout << "\n";
        }

    return 0;
}
