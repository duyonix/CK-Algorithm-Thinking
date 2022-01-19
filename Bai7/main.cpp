#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

int n;
int *a;
int *b;

void readData()
{
    fstream f;
    f.open("./input.txt", ios::in);
    f >> n;
    a = new int[n];
    b = new int[n];
    for (size_t i = 0; i < n; i++)
        f >> a[i];

    for (size_t i = 0; i < n; i++)
        f >> b[i];

    f.close();
}

int lcs(int m, int n)
{
    if (m == -1 || n == -1)
        return 0;
    if (a[m] == b[n])
        return 1 + lcs(m - 1, n - 1);
    else
        return max(lcs(m, n - 1), lcs(m - 1, n));
}
int main()
{
    readData();
    cout << "output: " << lcs(n - 1, n - 1);
    return 0;
}