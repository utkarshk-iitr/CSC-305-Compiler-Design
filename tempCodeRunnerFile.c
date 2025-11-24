#include <iostream>

struct A
{
    int i;    // 4 bytes
    char c1;  // 1 byte
    char c2;  // 1 byte
    double d; // 8 bytes
    int j;    // 4 bytes
    int o;
    char c3;
    int c[3];
}; // total = 4 + 1 + 1 + padding(2) + 8 + 4 = 20 bytes

int main()
{
    struct A a;
    printf("Size of struct A: %zu bytes\n", sizeof(a));

    printf("Address of a: %x\n", (void *)&a);
    printf("Address of a.i: %x\n", (void *)&a.i);
    printf("Address of a.c1: %x\n", (void *)&a.c1);
    printf("Address of a.c2: %x\n", (void *)&a.c2);
    printf("Address of a.d: %x\n", (void *)&a.d);
    printf("Address of a.j: %x\n", (void *)&a.j);
    printf("Address of a.o: %x\n", (void *)&a.o);
    printf("Address of a.c3: %x\n", (void *)&a.c3);
    printf("Address of a.c: %x\n", (void *)&a.c);
    printf("Address of a.c: %x\n", (void *)&a.c[0]);
    printf("Address of a.c: %x\n", (void *)&a.c[1]);
    printf("Address of a.c: %x\n", (void *)&a.c[2]);
    printf("Address of a.c: %x\n", (void *)&a.c[3]);

    int c;
    cin >> c;
    constexpr int b = c;
    return 0;
}