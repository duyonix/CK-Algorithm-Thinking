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
        static bool compareSlope(point A, point B) //xếp theo góc hợp bởi phương ngang 
                                                    //Nếu AOx < BOx thì A đứng trước
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

// <0 => a nằm bên trái so với bờ bc
// >0 => nằm bên phải
// =0 =>fail vì đề yêu cầu ko có 3 điểm nào thẳng hàng
long long location(point a, point b, point c) {
    return (b.getX() - a.getX()) * (b.getY() + a.getY()) + (c.getX() - b.getX()) * (c.getY() + b.getY()) + (a.getX() - c.getX()) * (a.getY() + c.getY());
}

// O(n^3)
// xét k nằm phía nào so với bờ ij
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
//sort 
//điểm chính giữa là i
//sau đó xét từ nửa tập sau i là j=i+1
//rồi xét k nằm phía nào so với bờ ij
pair<int, int> better(vector<point> a,int n) {
    sort(a.begin(), a.end());
    int i = n / 2 - 1;
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
            return make_pair(a[i].getId() + 1, a[j].getId() + 1);
        }
    }
    return make_pair(-1, -1);
}
point point::O = point(-1,0, 0);
//O(n)
pair<int, int> best(vector<point> a, int n) {
    int pos_O;
    long long x, y, min_x = LONG_MAX;
    for (int i =0; i <n; ++i)
    {
        x = a[i].getX();

        // Tìm điểm có hoành độ nhỏ nhất, nếu bằng thì lấy điểm hoành độ nhỏ nhất đầu tiên
        // Phải chọn điểm có hoành độ min vì khi xét góc hợp với phương ngang thì mỗi góc đều < 180 độ
        if (x < min_x)
        {
            min_x = x;
            pos_O = i;
        }
    }

    // Loại gốc ra khỏi mảng
    point tree_O = a[pos_O];
    if (pos_O != n - 1)
    {
        a[pos_O] = a[n - 1];
    }
    a.pop_back();
    point::O = tree_O;

    //Sắp xếp mảng theo góc hợp phương ngang , tưởng tượng sort các điểm theo vòng kim đồng hồ
    sort(a.begin(), a.end(), point::compareSlope);

    //Điểm chính giữa là kết quả
    point tree_O2 = a[a.size() / 2];
    return make_pair(tree_O.getId(), tree_O2.getId());
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
        //pair<int, int> ans = better(a,n);
        pair<int, int> ans = best(a, n);
        cout << ans.first+1 << " " << ans.second+1  << "\n";
    }
    return 0;
}