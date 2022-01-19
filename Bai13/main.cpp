#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#pragma warning(disable:4996)
const int N = 1000009;
class point {
    private:
        int id;
        long long x;
        long long y;

    public:
        static point O;
        bool operator<(const point& rhs) const {
            return x < rhs.x || (x == rhs.x && y < rhs.y);
        }
        point(int id, long long x, long long y) : id(id), x(x), y(y) {}
        point(const point& another) : x{ another.x }, y{ another.y }, id{ another.id } {}
        int getId() { return id; }
        long long getX() { return x; }
        long long getY() { return y; }
        static bool compareSlope(point A, point B)
        {
            double slope_a, slope_b;
            if (A.getX() == point::O.getX())
            {
                if (A.getY() - point::O.getY() > 0)
                    slope_a = DBL_MAX;
                else
                    slope_a = -DBL_MAX;
            }
            else
                slope_a = (A.getY() - point::O.getY()) * 1.0 / (A.getX() - point::O.getX());

            if (B.getX() == point::O.getX())
            {
                if (B.getY() - point::O.getY() > 0)
                    slope_b = DBL_MAX;
                else
                    slope_b = -DBL_MAX;
            }
            else
                slope_b = (B.getY() - point::O.getY()) * 1.0 / (B.getX() - point::O.getX());

            return slope_a > slope_b;

        }
};


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
point point::O = point(0, 0, -1);
//O(n)
pair<int, int> best(vector<point> a, int n) {
    int x, y, pos_O;
    int min_x = INT_MAX;
    for (int i = 1; i <= n; ++i)
    {
        cin >> x >> y;
        a.push_back(point(x, y, i));

        // tim O co hoanh do x nho nhat
        if (x < min_x)
        {
            min_x = x;
            pos_O = i - 1;
        }
    }

    // loai diem tree_O ra khoi mang, va tree_O tro thanh goc
    point tree_O = a[pos_O];
    if (pos_O != n - 1)
    {
        a[pos_O] = a[n - 1];
    }
    a.pop_back();
    point::O = tree_O;

    // sap xep mang theo do doc cua tree_O
    sort(a.begin(), a.end(), point::compareSlope);

    // diem trung vi tree_O2
    point tree_O2 = a[a.size() / 2];
    return make_pair(pos_O, tree_O2.getId());
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
        //pair<int, int> ans = best(a, n);
        cout << ans.first+1 << " " << ans.second +1 << "\n";
    }
    return 0;
}