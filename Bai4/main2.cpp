#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1000;

int n, s, a[N] = {};

// Ý tưởng: duyệt tất cả các cặp i, j (0 <= i < j < n) thỏa a[i] + a[j] <= m
int FM_getall(int a[], int n, int s)
{
    int result = 0;

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] + a[j] <= s)
            {
                result++;
            }
    return result;
}

// Ý tưởng: sắp xếp mảng đầu vào, khi đó nếu 2 số r, l (0 <= l < r < n) thỏa a[l] + a[r] <= m (*)
// thì sẽ có r-l cặp số thảo yêu cầu (các cắp này là <l, l+1>, <l, l+2>,..., <l, r>), tăng l lên 1
// nếu không thỏa (*) thì giảm r đi 1. Lắp lại tới khi l >= r.
int FM_2pointer(int a[], int n, int s)
{
    int l = 0, r = n - 1;
    int result = 0;

    while (l < r)
    {
        if (a[l] + a[r] <= s)
        {
            result += (r - l);
            l++;
        }
        // giảm r để chuyển đến giá trị nhỏ hơn.
        else
            r--;
    }
    return result;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> n >> s;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a, a + n);

    // cout << FM_getall(a, n, s) << endl;
    cout << FM_2pointer(a, n, s) << endl;

    return 0;
}
