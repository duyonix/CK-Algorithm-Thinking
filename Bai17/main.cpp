#include <iostream>
#include <cmath>
#include <sstream>
using namespace std;

// print all binary sequences with length n
string *getAllBinary(int n)
{
    string *allBinary = new string[(int)pow(2, n)];
    int count = 0;

    int i, j;
    int a[n];
    for (i = 0; i < n; i++)
        a[i] = 0;

    string currentBin = "";
    while (true)
    {
        // lấy kết quả hiện tại
        currentBin = "";
        for (i = 0; i < n; i++)
            currentBin += a[i] + '0';
        allBinary[count++] = currentBin;

        // tìm vị trí đầu tiên có giá trị là 0
        i = n - 1;
        while (i >= 0 && a[i] == 1)
            i--;
        // không có thì dừng (đã tìm hết, 1111...1111)
        if (i < 0)
            break;

        // nếu tìm tháy thì set vị trí đó là 1, và những vị trí sau là 0
        a[i] = 1;
        for (j = i + 1; j < n; j++)
            a[j] = 0;
    }

    return allBinary;
}

int stringToInt(string s)
{
    stringstream ss(s);
    int n;
    ss >> n;
    ss.clear();
    return n;
}

int findM_Naive(int n)
{
    // lướt qua tất cả các dãy nhị phân độ dài 9 bắt đầu từ 000000001
    // tìm thấy dãy nhị phân là bội của n thì dừng

    int m = -1;

    string *allBinary = getAllBinary(9);
    int lim = (int)pow(2, 9);
    for (int i = 1; i < lim; i++)
    {
        int current = stringToInt(allBinary[i]);
        if (current % n == 0)
        {
            m = current;
            break;
        }
    }

    delete[] allBinary;
    return m;
}

int main()
{
    int n;
    cin >> n;
    cout << findM_Naive(n);
}