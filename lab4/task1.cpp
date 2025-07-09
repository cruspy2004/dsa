#include <iostream>
using namespace std;

// Node class for Doubly Linked List
class DoublyListNode {
public:
    int data;
    DoublyListNode* next;
    DoublyListNode* prev;
    
    DoublyListNode() {
        data = 0;
        next = nullptr;
        prev = nullptr;
    }
    
    DoublyListNode(int value) {
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};

// Node class for Circular Linked List
class CircularListNode {
public:
    int data;
    CircularListNode* next;
    
    CircularListNode() {
        data = 0;
        next = nullptr;
    }
    
    CircularListNode(int value) {
        data = value;
        next = nullptr;
    }
};

// Doubly Linked List Class
class DoublyLinkedList {
public:
    DoublyListNode* first;
    DoublyListNode* last;
    DoublyListNode* PredLoc_;
    DoublyListNode* Loc_;
    
    DoublyLinkedList() {
        first = nullptr;
        last = nullptr;
        PredLoc_ = nullptr;
        Loc_ = nullptr;
    }
    
    bool IsEmpty() {
        return first == nullptr;
    }
    
    void InsertAtFront(int value) {
        DoublyListNode* newnode = new DoublyListNode(value);
        
        if (IsEmpty()) {
            // Insertion into empty list
            first = newnode;
            last = newnode;
        } else {
            // Insertion at front of existing list
            newnode->next = first;
            first->prev = newnode;
            first = newnode;
        }
    }
    
    void InsertAtEnd(int value) {
        DoublyListNode* newnode = new DoublyListNode(value);
        
        if (IsEmpty()) {
            // Insertion into empty list
            first = newnode;
            last = newnode;
        } else {
            // Insertion at end of existing list
            last->next = newnode;
            newnode->prev = last;
            last = newnode;
        }
    }
    
    void Search(int value) {
        PredLoc_ = nullptr;
        Loc_ = nullptr;
        
        if (IsEmpty()) return;
        
        DoublyListNode* temp = first;
        
        while (temp != nullptr) {
            if (temp->data == value) {
                Loc_ = temp;
                return;
            }
            if (temp->data < value) {
                PredLoc_ = temp;
            }
            temp = temp->next;
        }
    }
    
    void InsertSorted(int value) {
        Search(value);
        
        if (Loc_ != nullptr) {
            // Value already exists
            return;
        }
        
        DoublyListNode* newnode = new DoublyListNode(value);
        
        if (PredLoc_ == nullptr) {
            // Insert at front
            InsertAtFront(value);
            delete newnode;
        } else if (PredLoc_ == last) {
            // Insert at end
            InsertAtEnd(value);
            delete newnode;
        } else {
            // Insert in middle
            newnode->next = PredLoc_->next;
            newnode->prev = PredLoc_;
            PredLoc_->next->prev = newnode;
            PredLoc_->next = newnode;
        }
    }
    
    int DeleteFront() {
        if (IsEmpty()) {
            cout << "List is empty!" << endl;
            return -1;
        }
        
        DoublyListNode* temp = first;
        int value = temp->data;
        
        if (first == last) {
            // Only one node
            first = nullptr;
            last = nullptr;
        } else {
            first = first->next;
            first->prev = nullptr;
        }
        
        delete temp;
        return value;
    }
    
    int DeleteLast() {
        if (IsEmpty()) {
            cout << "List is empty!" << endl;
            return -1;
        }
        
        DoublyListNode* temp = last;
        int value = temp->data;
        
        if (first == last) {
            // Only one node
            first = nullptr;
            last = nullptr;
        } else {
            last = last->prev;
            last->next = nullptr;
        }
        
        delete temp;
        return value;
    }
    
    void Delete(int value) {
        Search(value);
        
        if (Loc_ == nullptr) {
            cout << "Value not found!" << endl;
            return;
        }
        
        if (Loc_ == first) {
            DeleteFront();
        } else if (Loc_ == last) {
            DeleteLast();
        } else {
            Loc_->prev->next = Loc_->next;
            Loc_->next->prev = Loc_->prev;
            delete Loc_;
        }
    }
    
    void DestroyList() {
        while (!IsEmpty()) {
            DeleteFront();
        }
    }
    
    void Display() {
        if (IsEmpty()) {
            cout << "List is empty!" << endl;
            return;
        }
        
        DoublyListNode* temp = first;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    
    // Task 1.1: Rearrange nodes by grouping even and odd values
    void RearrangeEvenOdd() {
        if (IsEmpty() || first == last) return;
        
        DoublyListNode* evenHead = nullptr;
        DoublyListNode* evenTail = nullptr;
        DoublyListNode* oddHead = nullptr;
        DoublyListNode* oddTail = nullptr;
        
        DoublyListNode* current = first;
        
        while (current != nullptr) {
            DoublyListNode* next = current->next;
            
            // Disconnect current node
            current->next = nullptr;
            current->prev = nullptr;
            
            if (current->data % 2 == 0) {
                // Even number
                if (evenHead == nullptr) {
                    evenHead = evenTail = current;
                } else {
                    evenTail->next = current;
                    current->prev = evenTail;
                    evenTail = current;
                }
            } else {
                // Odd number
                if (oddHead == nullptr) {
                    oddHead = oddTail = current;
                } else {
                    oddTail->next = current;
                    current->prev = oddTail;
                    oddTail = current;
                }
            }
            
            current = next;
        }
        
        // Connect even and odd lists
        if (evenHead != nullptr && oddHead != nullptr) {
            evenTail->next = oddHead;
            oddHead->prev = evenTail;
            first = evenHead;
            last = oddTail;
        } else if (evenHead != nullptr) {
            first = evenHead;
            last = evenTail;
        } else if (oddHead != nullptr) {
            first = oddHead;
            last = oddTail;
        }
    }
    
    // Task 1.3: Swap two nodes by values
    void SwapNodes(int value1, int value2) {
        if (value1 == value2) return;
        
        DoublyListNode* node1 = nullptr;
        DoublyListNode* node2 = nullptr;
        
        // Find both nodes
        DoublyListNode* temp = first;
        while (temp != nullptr) {
            if (temp->data == value1) node1 = temp;
            if (temp->data == value2) node2 = temp;
            temp = temp->next;
        }
        
        if (node1 == nullptr || node2 == nullptr) {
            cout << "One or both values not found!" << endl;
            return;
        }
        
        // If nodes are adjacent
        if (node1->next == node2) {
            SwapAdjacentNodes(node1, node2);
        } else if (node2->next == node1) {
            SwapAdjacentNodes(node2, node1);
        } else {
            // Nodes are not adjacent
            SwapNonAdjacentNodes(node1, node2);
        }
    }
    
private:
    void SwapAdjacentNodes(DoublyListNode* first_node, DoublyListNode* second_node) {
        if (first_node->prev) first_node->prev->next = second_node;
        if (second_node->next) second_node->next->prev = first_node;
        
        second_node->prev = first_node->prev;
        first_node->next = second_node->next;
        
        first_node->prev = second_node;
        second_node->next = first_node;
        
        if (first == first_node) first = second_node;
        if (last == second_node) last = first_node;
    }
    
    void SwapNonAdjacentNodes(DoublyListNode* node1, DoublyListNode* node2) {
        DoublyListNode* temp;
        
        // Swap prev pointers
        temp = node1->prev;
        node1->prev = node2->prev;
        node2->prev = temp;
        
        // Swap next pointers
        temp = node1->next;
        node1->next = node2->next;
        node2->next = temp;
        
        // Update surrounding nodes
        if (node1->prev) node1->prev->next = node1;
        if (node1->next) node1->next->prev = node1;
        if (node2->prev) node2->prev->next = node2;
        if (node2->next) node2->next->prev = node2;
        
        // Update first and last pointers
        if (first == node1) first = node2;
        else if (first == node2) first = node1;
        
        if (last == node1) last = node2;
        else if (last == node2) last = node1;
    }
};

// Circular Linked List Class
class CircularLinkedList {
public:
    CircularListNode* last;
    CircularListNode* PredLoc_;
    CircularListNode* Loc_;
    
    CircularLinkedList() {
        last = nullptr;
        PredLoc_ = nullptr;
        Loc_ = nullptr;
    }
    
    bool IsEmpty() {
        return last == nullptr;
    }
    
    void InsertAtFront(int value) {
        CircularListNode* newnode = new CircularListNode(value);
        
        if (IsEmpty()) {
            // Insertion into empty list
            newnode->next = newnode;
            last = newnode;
        } else {
            // Insertion at front of existing list
            newnode->next = last->next;
            last->next = newnode;
        }
    }
    
    void InsertAtEnd(int value) {
        CircularListNode* newnode = new CircularListNode(value);
        
        if (IsEmpty()) {
            // Insertion into empty list
            newnode->next = newnode;
            last = newnode;
        } else {
            // Insertion at end of existing list
            newnode->next = last->next;
            last->next = newnode;
            last = newnode;
        }
    }
    
    void Display() {
        if (IsEmpty()) {
            cout << "List is empty!" << endl;
            return;
        }
        
        CircularListNode* temp = last->next;
        do {
            cout << temp->data << " ";
            temp = temp->next;
        } while (temp != last->next);
        cout << endl;
    }
    
    // Task 1.2: Reverse the circular linked list
    void Reverse() {
        if (IsEmpty() || last->next == last) return;
        
        CircularListNode* current = last->next;
        CircularListNode* prev = last;
        CircularListNode* next;
        
        do {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        } while (current != last->next);
        
        last = last->next;
    }
    
    void Search(int value) {
        PredLoc_ = nullptr;
        Loc_ = nullptr;
        
        if (IsEmpty()) return;
        
        CircularListNode* temp = last->next;
        CircularListNode* pred = nullptr;
        
        do {
            if (temp->data == value) {
                Loc_ = temp;
                PredLoc_ = pred;
                return;
            }
            pred = temp;
            temp = temp->next;
        } while (temp != last->next);
    }
    
    void DestroyList() {
        if (IsEmpty()) return;
        
        CircularListNode* current = last->next;
        while (current != last) {
            CircularListNode* temp = current;
            current = current->next;
            delete temp;
        }
        delete last;
        last = nullptr;
    }
};

// Test function
int main() {
    cout << "=== Doubly Linked List Tests ===" << endl;
    DoublyLinkedList dll;
    
    // Test basic operations
    dll.InsertAtEnd(3);
    dll.InsertAtEnd(1);
    dll.InsertAtEnd(4);
    dll.InsertAtEnd(2);
    dll.InsertAtEnd(5);
    dll.InsertAtEnd(6);
    
    cout << "Original list: ";
    dll.Display();
    
    // Test Task 1.1: Rearrange even and odd
    dll.RearrangeEvenOdd();
    cout << "After rearranging even/odd: ";
    dll.Display();
    
    // Reset list for swap test
    dll.DestroyList();
    dll.InsertAtEnd(10);
    dll.InsertAtEnd(20);
    dll.InsertAtEnd(30);
    dll.InsertAtEnd(40);
    
    cout << "\nList for swap test: ";
    dll.Display();
    
    // Test Task 1.3: Swap nodes
    dll.SwapNodes(20, 40);
    cout << "After swapping nodes with values 20 and 40: ";
    dll.Display();
    
    cout << "\n=== Circular Linked List Tests ===" << endl;
    CircularLinkedList cll;
    
    // Test circular list
    cll.InsertAtEnd(1);
    cll.InsertAtEnd(2);
    cll.InsertAtEnd(3);
    cll.InsertAtEnd(4);
    cll.InsertAtEnd(5);
    
    cout << "Original circular list: ";
    cll.Display();
    
    // Test Task 1.2: Reverse circular list
    cll.Reverse();
    cout << "After reversing: ";
    cll.Display();
    
    // Cleanup
    dll.DestroyList();
    cll.DestroyList();
    
    return 0;
}