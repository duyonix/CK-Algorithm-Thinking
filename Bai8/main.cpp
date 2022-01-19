#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

#define ll long long

int n;
int M;
int *a;
ll dp[200][200];

void readData()
{
    fstream f;
    f.open("./input.txt", ios::in);
    f >> n >> M;
    a = new int[n];
    for (size_t i = 0; i < n; i++)
        f >> a[i];

    f.close();
}

ll sum(int i, int j)
{
    ll res = 0;
    for (int k = i; k <= j; k++)
    {
        res += a[k];
        res %= M;
        }
    return res;
}

ll solve(int i, int j)
{
    // base case
    if (i >= j)
        return 0;
    // check if already calculated
    if (dp[i][j] != -1)
        return dp[i][j];

    dp[i][j] = LLONG_MAX;
    for (int k = i; k < j; k++)
    {
        dp[i][j] = min(dp[i][j], solve(i, k) + solve(k + 1, j) + sum(i, k) * sum(k + 1, j));
    }
    return dp[i][j];
}
int main()
{
    readData();

    // init dp
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dp[i][j] = -1;

    cout << "output: " << solve(0, n - 1);
    return 0;
}