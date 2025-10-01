#include <bits/stdc++.h>

using namespace std;

int main()
{
    int **a = new int *[10];
    cout << *a << endl;
    delete a;
    cout << *a << endl; // Undefined behavior: accessing deleted memory
    return 0;
}