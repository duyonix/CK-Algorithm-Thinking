#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <utility>
using namespace std;

class state // một trạng thái trong quá trình tìm kiếm
{
public:
    int g; // số lần lật mảng
    vector<int> array;

public:
    state(int g, vector<int> array)
    {
        this->g = g;
        this->array = std::move(array);
    }
    state(int g, const state &s) // tạo mội trạng thái mới từ trạng thái cũ đồng thởi thay đổi g (số lần lật).
    {
        this->g = g;
        this->array = s.array;
    }
    int F_function()
    {
        int result = 0;
        for (int i = 0; i < array.size() - 1; i++)
            if (abs(array[i] - array[i + 1]) != 1)
                result++;

        return g + result;
    }
    void flip(int i)
    {
        int temp, start = 0;
        while (start < i)
        {
            temp = array[start];
            array[start] = array[i];
            array[i] = temp;
            start++;
            i--;
        }
    }
    void print()
    { // in trạng thái hiện tại, chỉ để kiểm tra
        cout << "Flip: " << g << " - { ";
        for (int i : array)
        {
            cout << i << " ";
        }
        cout << " } - f = " << this->F_function() << endl;
    }
};

struct compare
{
    bool operator()(state a, state b)
    {
        return a.F_function() > b.F_function();
    }
};

class AStar
{
public:
    vector<int> start;
    vector<int> goal;
    priority_queue<state, vector<state>, compare> open;
    set<vector<int>> close;

public:
    AStar(const vector<int> &start, const vector<int> &goal)
    {
        this->start = start;
        this->goal = goal;
    }

    int minimum()
    {
        open.push(state(0, start));
        while (!open.empty())
        {
            state cur = open.top();
            if (cur.array == goal)
            {
                return cur.g;
            }
            close.insert(cur.array);

            for (int i = 1; i < cur.array.size(); i++)
            {
                state next(cur.g + 1, cur); // tăng số lần lật mảng lên 1.
                next.flip(i);

                if (close.find(next.array) == close.end())
                {
                    open.push(next);
                }
            }
            open.pop();
        }
        return -1; // Trả về -1 nếu không tìm thấy kết quả.
                   // Nhưng điều này không thể xảy ra, bài toán luôn có lới giải.
    }
};

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;
    vector<int> start(n); //= {5, 2, 3, 4, 1};
    vector<int> goal(n);

    for (int i = 0; i < n; i++)
    {
        cin >> start[i];
        goal[i] = i + 1;
    }

    AStar a_star(start, goal);
    cout << a_star.minimum() << endl;
    return 0;
}