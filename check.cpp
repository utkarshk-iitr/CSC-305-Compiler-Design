#include <bits/stdc++.h>

using namespace std;

int main()
{
    const static int b = 5;
    cout << b << endl;
    int a = stoi("9875");
    cout << a << endl;
    // int arr[3][2] = {1, 2, 3, 4, 5, 6};

    int p = 10;

    int arr[2][3] = {{1, 2}, {4, 5, 6}};
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    int *c, *d;
    return 0;
}