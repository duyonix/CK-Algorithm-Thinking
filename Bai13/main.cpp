#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#pragma warning(disable:4996)
class point {
    private:
        int id;
        long long x;
        long long y;

    public:
        bool operator<(const point& rhs) const {
            return x < rhs.x || (x == rhs.x && y < rhs.y);
        }
        point(int id, long long x, long long y) : id(id), x(x), y(y) {}
        int getId() { return id; }
        int getX() { return x; }
        int getY() { return y; }
};
const int N = 1000009;

long long location(point a, point b, point c) {
    return (b.getX() - a.getX()) * (b.getY() + a.getY()) + (c.getX() - b.getX()) * (c.getY() + b.getY()) + (a.getX() - c.getX()) * (a.getY() + c.getY());
}

// O(n^3)
pair<int, int> naive(vector<point> a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int leftSide = 0;
            int rightSide = 0;
            for (int k = 0; k < n; k++) {
                if (k == i || k == j) {
                    continue;
                }
                if (location(a[k], a[i], a[j]) > 0) {
                    leftSide += 1;
                }
                else {
                    rightSide += 1;
                }
            }

            if (leftSide == rightSide) {
                return make_pair(i + 1, j + 1);
            }
        }
    }
    return make_pair(-1, -1);
}
//O(n^2)
pair<int, int> better(vector<point> a,int n) {
    sort(a.begin(), a.end());
    int i = n / 2 - 1;
    for (int j = i + 1; j < n; j++) {
        int left_side = 0;
        int right_side = 0;
        for (int k = 0; k < n; k++) {
            if (k == i || k == j) {
                continue;
            }
            if (location(a[k], a[i], a[j]) > 0) {
                left_side += 1;
            }
            else {
                right_side += 1;
            }
        }

        if (left_side == right_side) {
            return make_pair(a[i].getId() + 1, a[j].getId() + 1);
        }
    }
    return make_pair(-1, -1);
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    vector<point> a;
    cin >> n;
    if (n % 2 != 0) cout << "-1 -1";
    else {
        a.clear();
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            a.push_back(point(i, x, y));
        }

        //pair<int, int> ans = naive();
        pair<int, int> ans = better(a,n);
        cout << ans.first + 1 << " " << ans.second + 1 << "\n";
    }
    return 0;
}