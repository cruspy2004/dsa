#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Recursive function to calculate Factorial
int factorialRecursive(int n) {
    if(n <2 ){
        return 1 ;
    }
    else return n *factorialRecursive(n-1);
}

// Iterative Function to calculate Factorial
int factorialIterative(int n){
    if(n <2 ){
        return 1 ;
    }
    else {
        int ans = 1  ;
        for ( int i = n ;i >0 ; i--  ){
            ans *= i ; 
        }
        return ans ;
    }
}

int main(){
    cout <<"Enter the number to calculate the factorial for: ";
    int n;
    cin >> n;

    cout << "Factorial of " << n << " is(recursively): ";
    auto start = high_resolution_clock::now();
    cout << factorialRecursive(n) << endl;  
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken (recursively): " << duration.count() << " microseconds" << endl;


    cout << "Factorial of " << n << " is(Iteratively): ";
     start = high_resolution_clock::now();
    cout << factorialIterative(n) << endl;  
     stop = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop - start);
    cout << "Time taken (Iteratively): " << duration2.count() << " microseconds" << endl;
}