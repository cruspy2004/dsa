#include <iostream>
using namespace std;

int main(){

    cout << "size of int " << sizeof(int) << endl; // This line now correctly outputs the size of int.
    cout << "size of float " <<sizeof(float)<< endl; // This line is a no-op, it does nothing.
    cout <<"size of long " << sizeof(long)<< endl; // This line is a no-op, it does nothing.
    cout <<"size of char " << sizeof(char)<< endl; // This line is a no-op, it does nothing.
    cout <<"size of double" << sizeof(double)<< endl; // This line is also a no-op, it does nothing.

}