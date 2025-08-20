#include <iostream>
#define MAX 100 // Maximum patients allowed

class node {
public:
    int data;
    node* next;

    node() : data(0), next(nullptr) {};
    node(int value) : data(value), next(nullptr) {};

};

class LLStack {
    private: 
    node* top;
public:
    LLStack() : top(nullptr) {};
    bool isEmpty() {
        return top == nullptr;
    }
    void Push(int value) {
        node* newNode = new node(value);
        newNode->next = top;
        top = newNode;
    }
    int Pop() {
        if (isEmpty()) {
            std::cout << "Stack Underflow!" << std::endl;
            return -1; // or throw an exception
        }
        node* temp = top;
        int value = top->data;
        top = top->next;
        delete temp;
        return value;
    }
    int Peek() {
        if (isEmpty()) {
            std::cout << "Stack is empty!" << std::endl;
            return -1; // or throw an exception
        }
        return top->data;
    }
    void Clear() {
        while (!isEmpty()) {
            Pop();
        }
    }
    ~LLStack() {
        Clear();
    }
};

int main() {
    LLStack stack;
    stack.Push(10);
    stack.Push(20);
    std::cout << "Top element: " << stack.Peek() << std::endl; // Should print 20
    std::cout << "Popped element: " << stack.Pop() << std::endl; // Should print 20
    std::cout << "Top element after pop: " << stack.Peek() << std::endl; // Should print 10
    stack.Clear();
    return 0;
}