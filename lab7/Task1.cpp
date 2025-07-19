#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;


// Recursive function to calculate Fibonacci
int fibonacciRecursive(int n) {
    if (n <= 1)
        return n;  // Base case: fib(0) = 0, fib(1) = 1
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);  // Recursive step
}

int fibonacciIterative(int n) {
    if (n <= 1)
        return n;  // Base case
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;  // Calculate next Fibonacci number
        a = b;      // Update a to the previous b
        b = c;      // Update b to the current Fibonacci number
    }
    return b;  // Return the nth Fibonacci number
}

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    cout << "Fibonacci series up to " << n << ":\n";
    cout<<"recursive:";
    
    for (int i = 0; i <= n; i++) {
        auto start = high_resolution_clock::now();
        cout << fibonacciRecursive(i) << " ";
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "[Time taken(recursive): " << duration.count() << " microseconds]"<< endl;
    }
    cout << "\niterative:";
    for (int i = 0; i <= n; i++) {
        auto start = high_resolution_clock::now();
        cout << fibonacciIterative(i) << " ";
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "[Time taken(Iterative): " << duration.count() << " microseconds]"<< endl;
    }
    return 0;
}
