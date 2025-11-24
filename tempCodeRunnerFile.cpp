#include <iostream>

class A{
    public:
    char a,b,c;
};

void fn(A a){
    a.c = 'a';
    a.a = 'b';
    a.b = 'c';
    return;
}

int main(){
    const int a = 5;
    int* p = (int*)&a;
    *p = 10;
    std::cout << *(&a); // Undefined behavior
    return 0;
}