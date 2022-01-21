#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <map>
#include <iterator>

using namespace std;
int n, m, k;
const long long base = round(1e9) + 7;
struct matran
{
    int a[55][55];
};
matran nhanmatran(matran a, matran b)
{
    matran tmp;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            tmp.a[i][j] = 0;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            for (int k = 1; k <= n; ++k)
            {
                tmp.a[i][j] += a.a[i][k] * b.a[k][j];
                tmp.a[i][j] %= base;
            }
        }
    }
    return tmp;
}
matran mu(matran a, long long k)
{
    if (k == 1)
    {
        return a;
    }
    long long tmp = k / 2;
    matran x = mu(a, k / 2);
    x = nhanmatran(x, x);
    if (k % 2 == 0)
        return x;
    else
        return nhanmatran(x, a);
}
int main()
{
    ifstream f;
    f.open("input.txt");

    f >> n >> m >> k;
    matran coban;
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        f >> u >> v;
        coban.a[u][v]++;
    }
    matran res = mu(coban, k);
    int q;
    f >> q;
    for (int i = 1; i <= q; ++i)
    {
        int u, v;
        f >> u >> v;
        cout << res.a[u][v] << "\n";
    }
}