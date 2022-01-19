#include <bits/stdc++.h>
using namespace std;

const long long MAXN = 1e6;
const long long MAXX = 1e9;

int n;
long long a[MAXN], gt[21], th[21];
bool visited[MAXN];
int k;

int timChiSo()
{
    int res = 0;
    int l = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
            if (a[j] < a[i])
                l++;
        res += (gt[n - i - 1] * gt[a[i] - 1 - l]);
    }
    return ++res;
}
void timChuoi()
{
    for (int i = 0; i < n; i++)
        for (int j = 1; j <= n; j++)
        {
            if (gt[n - i - 1] * j >= k || i == n - 1)
            {
                int c = 0;
                for (int h = 1; h <= n; h++)
                {
                    if (!visited[h])
                        c++;
                    if (c == j)
                    {
                        k -= gt[n - i - 1] * (j - 1);
                        visited[h] = true;
                        cout << h << " ";
                        break;
                    }
                }
                break;
            }
        }
}
int main()
{
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);
    int x;
    while (cin >> x)
    {
        a[n++] = x;
    }
    k = a[--n];

    gt[1] = 1;
    th[1] = 1;
    for (int i = 2; i <= 21; i++)
    {
        gt[i] = gt[i - 1] * i;
        th[i] = th[i - 1] * gt[i];
    }
    cout << timChiSo() << "\n";
    timChuoi();
}