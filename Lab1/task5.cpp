#include <iostream>
using namespace std;


void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}
void swapByDoublePointer(int **x, int **y) {
    int temp = **x;
    **x = **y;
    **y = temp;
}

int main(){

    int a=5, b=10; 
	int *pa=&a; //pa and pb are pointer variables of type int. 
	int *pb=&b;
	
	int **ppa=&pa; //ppa and ppb are called double pointers or pointers-to-pointers.
	int **ppb=&pb;

    cout << "Before swap: a = " << a << ", b = " << b << endl;
    
    // Swapping using double pointers
    swap(&a, &b);
    
    cout << "After swap: a = " << a << ", b = " << b << endl;

    // Displaying addresses
    cout << "Address of a: " << &a << ", Address of b: " << &b << endl;
    cout << "Address stored in pa: " << pa << ", Address stored in pb: " << pb << endl;
    cout << "Address stored in ppa: " << ppa << ", Address stored in ppb: " << ppb << endl;

        // Swapping using double pointers
    swapByDoublePointer(ppa, ppb);
    
    cout << "After swap: a = " << a << ", b = " << b << endl;

    // Displaying addresses
    cout << "Address of a: " << &a << ", Address of b: " << &b << endl;
    cout << "Address stored in pa: " << pa << ", Address stored in pb: " << pb << endl;
    cout << "Address stored in ppa: " << ppa << ", Address stored in ppb: " << ppb << endl;


}


