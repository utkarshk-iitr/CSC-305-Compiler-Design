struct A {
    int    i;      // 4 bytes
    char   c1;     // 1 byte
    char   c2;     // 1 byte
    double d;      // 8 bytes
    int    j;      // 4 bytes
};  // total = 4 + 1 + 1 + padding(2) + 8 + 4 = 20 bytes

int main() {
    struct A a;
    printf("Size of struct A: %zu bytes\n", sizeof(a));
    return 0;
}