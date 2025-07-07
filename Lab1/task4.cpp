#include <iostream>
using namespace std;

void main(){

    int x[4] = {0,4,6,9};
    int *p, a=3;
    p=x;
    (*p)++;
    cout<<*p<<endl;
    cout<<*(p+1)<<endl;
    p++; //x[1] = 2
    *p=*p+a;
    cout<<*p<<endl;
    p=p+2; //What is happening here?
    cout<<*p<<endl;


}


