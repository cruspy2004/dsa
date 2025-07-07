#include <iostream>
#include <unordered_set>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = nullptr;
    }
};

class SinglyLinkedList {
private:
    Node* head;

public:
    SinglyLinkedList() {
        head = nullptr;
    }

    void insertAtEnd(int val){
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    };
    void insertAtBeginning(int val){
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    };
    void insertAtPosition(int val, int pos){
        Node* newNode = new Node(val);
        if (pos == 0) {
            insertAtBeginning(val);
            return;
        }
        Node* temp = head;
        for (int i = 0; i < pos - 1 && temp != nullptr; i++) {
            temp = temp->next;
        }
        if (temp == nullptr) {
            cout << "Position out of bounds. Inserting at end instead.\n";
            insertAtEnd(val);
            return;
        }
        newNode->next=temp->next;
        temp->next = newNode;
        return;
    };
    void deleteFromBeginning(){
        if (!head) {
            cout << "List is empty. Nothing to delete.\n";
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    };
    void deleteFromEnd(){
        if (!head) {
            cout << "List is empty. Nothing to delete.\n";
            return;
        }
        if (!head->next) {
            delete head;
            head = nullptr;
            return;
        }
        Node* temp = head;
        while (temp->next && temp->next->next) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    };
    void deleteFromPosition(int pos){
        if (!head) {
            cout<< "List is empty. Nothing to delete.\n";
            return; 
        }
        if (pos == 0) { 
            deleteFromBeginning();
            return;
        }
        Node* temp = head;
        for (int i = 0; i < pos - 1 && temp != nullptr; i++) {
            temp = temp->next;
        }   

        if (temp == nullptr || temp->next == nullptr) {
            cout << "Position out of bounds. Nothing to delete.\n";
            return;
        }
        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
        return;
    };
    void reverse(){
        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;
        while (current != nullptr) {
            next = current->next; // Store next node
            current->next = prev; // Reverse the link
            prev = current;       // Move prev to current
            current = next;       // Move to next node
        }
        head = prev; // Update head to new first node
    };
    bool detectLoop(){
        Node* slow = head;
        Node* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;          // Move slow by 1
            fast = fast->next->next;   // Move fast by 2
            if (slow == fast) {
                return true; // Loop detected
            }
        }
        return false; // No loop detected
    };
    void removeDuplicates(){
        unordered_set<int> seen;
        Node* current = head;
        Node* prev = nullptr;

        while (current != nullptr) {
            if (seen.find(current->data) != seen.end()) {
                // Duplicate found, remove it
                prev->next = current->next;
                delete current;
                current = prev->next; // Move to next node
            } else {
                // Not a duplicate, add to set
                seen.insert(current->data);
                prev = current;
                current = current->next;
            }
        }
    };
void mergeSort() {
    head = mergeSortUtil(head);
}

Node* mergeSortedLists(Node* l1, Node* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    if (l1->data < l2->data) {
        l1->next = mergeSortedLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeSortedLists(l1, l2->next);
        return l2;
    }
}

Node* mergeSortUtil(Node* node) {
    if (!node || !node->next) return node;  // Base case: 0 or 1 node

    // Find middle using slow & fast pointers
    Node* slow = node;
    Node* fast = node->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* mid = slow->next;
    slow->next = nullptr;  // Split into two halves

    Node* left = mergeSortUtil(node);
    Node* right = mergeSortUtil(mid);

    return mergeSortedLists(left, right);
}

void display() {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}
};
// --------- Function Prototypes ---------- 


// --------- Implementations go here ----------

int main() {
    SinglyLinkedList list;

    list.insertAtEnd(5);
    list.insertAtEnd(10);
    list.insertAtBeginning(1);
    list.insertAtPosition(7, 2);
    list.display();

    cout << "Reversing list...\n";
    list.reverse();
    list.display();

    cout << "Detecting loop: " << (list.detectLoop() ? "Loop Found" : "No Loop") << endl;

    // You can create two sorted lists and merge them here
    // Additional logic to test merge, remove duplicates, and merge sort

    return 0;
}