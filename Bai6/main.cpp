#include <iostream>
#include <cmath>
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

using namespace std;

const int MAXV = 1e6 + 60;
const int MAXN = 1e3 + 30;
int c[MAXV], d[MAXV], e[MAXV];
int n, l, r;
int L[MAXN], R[MAXN];

int solution()
{
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (e[R[i]] < l || R[i] < l || L[i] > r || e[R[i]] < L[i])
        {
            ans = max(ans, R[i] - L[i]);
        }
    }
    return ans;
}

void input()
{
    cin >> n >> l >> r;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        L[i] = x;
        R[i] = y;
        c[x]++;
        c[y + 1]--;
    }
    c[0] = d[0];
    for (int i = 1; i < MAXV; i++)
    {
        d[i] = d[i - 1] + c[i];
    }
    for (int i = 0; i < MAXV; i++)
    {
        if (d[i] == 1)
        {
            if (i > r)
                e[i] = e[i - 1];
            else
                e[i] = i;
        }
        else
            e[i] = e[i - 1];
    }
}

int main()
{
    freopen("input6_1.txt", "r", stdin);
    input();
    int ans = solution();
    cout << ans << "\n";
    return 0;
}
