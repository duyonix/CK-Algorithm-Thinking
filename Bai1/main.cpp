#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 1e3
#define ll long long
#define pii pair<int, int>

using namespace std;
// O(log(max(a,b)))
ll gcd(ll a, ll b)
{
    return b == 0 ? a : gcd(b, a % b);
}

// Naive
void solution()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    ll gcd_max = a[0];
    for (ll i = 0; i <= n - k; i++)
    {
        ll temp_gcd = a[i];
        for (ll j = i + 1; j < i + k; ++j)
        {
            temp_gcd = gcd(temp_gcd, a[j]);
            // cout << a[j] << " ";
        }
        // cout << endl;
        if (temp_gcd > gcd_max)
        {
            gcd_max = temp_gcd;
        }
    }

    cout << gcd_max << endl;
}

// Giảm số lần gọi hàm gcd
void solution1()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    // code
    ll gcd_max = a[0];
    cout << gcd_max << endl;
}

int main()
{
    freopen("input.inp", "r", stdin);
    // freopen("output.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solution();
    return 0;
}