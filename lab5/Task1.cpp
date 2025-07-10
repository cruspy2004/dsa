#include <iostream>
#include <string>
using namespace std;

#define MAX 1000 // Maximum size of stack

class Stack {
private:
    char arr[MAX];
    int top;
public:
    Stack() {
        top = -1;
    }

    void Push(char element) {
        if (!isFull()) {
            arr[++top] = element;
        } else {
            cout << "Stack Overflow!" << endl;
        }
    }

    char Pop() {
        if (!isEmpty()) {
            return arr[top--];
        } else {
            cout << "Stack Underflow!" << endl;
            return '\0';
        }
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == MAX - 1;
    }

    void Clear() {
        top = -1;
    }

    char Peek() {
        if (!isEmpty()) {
            return arr[top];
        } else {
            cout << "Stack is Empty!" << endl;
            return '\0';
        }
    }
};

// Function to check if the given character is an opening brace
bool isOpeningBrace(char ch) {
    return (ch == '(' || ch == '[' || ch == '{');
}

// Function to check if the given character is a closing brace
bool isClosingBrace(char ch) {
    return (ch == ')' || ch == ']' || ch == '}');
}

// Function to check if two braces match
bool isMatchingPair(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '[' && closing == ']') ||
           (opening == '{' && closing == '}');
}

// Function to check expression for balanced braces
void checkExpression(const string& expr) {
    Stack s;
    int errorPos = -1;

    for (int i = 0; i < expr.length(); ++i) {
        char ch = expr[i];

        if (isOpeningBrace(ch)) {
            s.Push(ch);
        } else if (isClosingBrace(ch)) {
            if (s.isEmpty()) {
                errorPos = i + 1;
                cout << "This expression is NOT correct e.g. error at character # " 
                     << errorPos << ". '" << ch << "' - no matching opening brace." << endl;
                return;
            }
            char topChar = s.Pop();
            if (!isMatchingPair(topChar, ch)) {
                errorPos = i + 1;
                cout << "This expression is NOT correct e.g. error at character # " 
                     << errorPos << ". '" << ch << "' - does not match '" << topChar << "'." << endl;
                return;
            }
        }
    }

    if (s.isEmpty()) {
        cout << "This expression is correct." << endl;
    } else {
        cout << "This expression is NOT correct e.g. error at character # "
             << expr.length() << ". '" << s.Peek() << "' - not closed." << endl;
    }
}

int main() {
    string expr;

    cout << "Enter an expression: ";
    getline(cin, expr);

    checkExpression(expr);

    return 0;
}
