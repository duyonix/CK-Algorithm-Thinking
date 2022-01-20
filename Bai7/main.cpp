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

// 2^n

int lcsRecursion(int m, int n)
{
    if (m == -1 || n == -1)
        return 0;
    if (a[m] == b[n])
        return 1 + lcsRecursion(m - 1, n - 1);
    else
        return max(lcsRecursion(m, n - 1), lcsRecursion(m - 1, n));
}

// n^2

int lcsDP()
{
    // a[i] b[j]  ~ dp[i+1][j+1]
    int dp[n + 1][n + 1];

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[n][n];
}
int main()
{
    readData();
    // cout << "output: " << lcsRecursion(n - 1, n - 1);
    cout << "output: " << lcsDP();
    return 0;
}