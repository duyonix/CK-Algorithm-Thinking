#include <bits/stdc++.h>
using namespace std;

const long long MAXN = 11;
const long long MAXX = 1e9;

int n;
long long T;
int a[MAXN];
int L[MAXN], R[MAXN];
int result = 0;

void calTLeft(int d)
{
    for (int i = 0; i < n; i++)
    {
        L[i] = 0;
    }

    int stop = n - 1;
    int prev = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        if (i != n - 1)
        {
            prev = a[i + 1] - d + 1;
            L[i] = L[i + 1] - prev + (i - stop);
        }

        if (stop == -1)
        {
            continue;
        }

        for (int j = stop; j >= -1; j--) // Đặt -1 để biết là duyệt tới cột đầu rồi
        {
            if (j == -1)
            {
                stop = j;
                break;
            }
            if (i - j + 1 > a[j] - d + 1)
            {
                stop = j;
                break;
            }
            L[i] += a[j] - d - (i - j) + 1;
        }
    }
}
void calTRight(int d)
{
    for (int i = 0; i < n; i++)
    {
        R[i] = 0;
    }

    int stop = 0;
    int prev = 0;

    for (int i = 0; i < n; i++)
    {
        if (i != 0)
        {
            prev = a[i - 1] - d + 1;
            R[i] = R[i - 1] - prev + (stop - i);
        }

        if (stop == n)
        {
            continue;
        }

        for (int j = stop; j <= n; j++)
        {
            if (j == n)
            {
                stop = j;
                break;
            }
            if (j - i + 1 > a[j] - d + 1)
            {
                stop = j;
                break;
            }
            R[i] += a[j] - d - (j - i) + 1;
        }
    }
}
void chatNhiPhan(int l, int r)
{
    if (l > r)
    {
        return;
    }
    int mid = (l + r) / 2;
    calTLeft(mid);
    calTRight(mid);

    int minn = MAXX;

    for (int i = 0; i < n; i++)
    {
        minn = min((L[i] + R[i] - (a[i] - mid + 1)), minn);
    }

    if (minn <= T)
    {
        result = mid;
        chatNhiPhan(l, mid - 1);
    }
    else
    {
        chatNhiPhan(mid + 1, r);
    }
}
int main()
{
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);
    int minn = MAXX;
    int maxx = -MAXX;
    cin >> n >> T;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        minn = min(minn, a[i]);
        maxx = max(maxx, a[i]);
    }
    chatNhiPhan(minn - T, maxx);
    cout << --result;
}