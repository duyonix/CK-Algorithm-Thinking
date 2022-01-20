#include <iostream>
#include <cmath>
#include <sstream>
using namespace std;
#define MAX_LENGTH 9

int arrToInt(int *a, int n)
{
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        res += a[i];
        if (i < n - 1)
            res *= 10;
    }
    return res;
}

int findM(int n)
{
    // xét hết các dãy nhị phân có độ dài 9 (tù 000000001), tìm ra bội nhỏ nhất của n

    int i, j;
    int *a = new int[MAX_LENGTH];
    for (i = 0; i < MAX_LENGTH - 1; i++)
        a[i] = 0;
    a[MAX_LENGTH - 1] = 1;

    string currentBin = "";
    while (true)
    {
        // kiểm tra kết quả hiện tại
        int current = arrToInt(a, MAX_LENGTH);
        if (current % n == 0)
            return current;

        // tìm vị trí đầu tiên có giá trị là 0
        i = MAX_LENGTH - 1;
        while (i >= 0 && a[i] == 1)
            i--;
        // không có thì dừng (đã tìm hết, 1111...1111)
        if (i < 0)
            break;

        // nếu tìm thấy thì set vị trí đó là 1, và những vị trí sau là 0
        a[i] = 1;
        for (j = i + 1; j < MAX_LENGTH; j++)
            a[j] = 0;
    }

    delete[] a;
    return -1;
}

int main()
{
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);

    int n;
    cin >> n;
    cout << findM(n);

    // for (n = 1; n <= 100; n++)
    //     cout << n << "\t" << findM(n) << endl;
}