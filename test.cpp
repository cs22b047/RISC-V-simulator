#include<iostream>
using namespace std;

int main(){
    int a = 10;
    int *x = &a;
    long int reg;
    reg = (long int )x;
    cout<<*(int *)x;
}
