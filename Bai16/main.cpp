#include <iostream>
#include <queue>
using namespace std;

int BFS(int **arr, int n, int start, bool **distCounted)
{
    bool *visited = new bool[n]{false};

    // tổng khoảng cách từ đỉnh start tới mọi đỉnh (trừ những cái đã tồn tại rồi)
    int distFromStartToAll = 0;
    // ý nghĩa g này y hệt g trong Dijkstra, A*
    int g = 1;

    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        // cout << u << " ";

        // biến này để tăng g cho đúng lúc
        bool hasNewNeighbors = false;
        for (int i = 0; i < n; i++)
        {
            if (arr[u][i] == 1 && !visited[i])
            {
                // khoảng cách từ đỉnh start tới đỉnh i (hay ngược lại) chưa được tính vào kết quả thì tính
                if (!distCounted[start][i] && !distCounted[i][start])
                {
                    distFromStartToAll += g;
                    distCounted[start][i] = true;
                    distCounted[i][start] = true;
                    // cout << start << "  " << u << " " << i << " - " << g << endl;
                }
                visited[i] = true;
                hasNewNeighbors = true;
                q.push(i);
            }
        }

        if (hasNewNeighbors)
            g++;
    }

    return distFromStartToAll;
}

int main()
{
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);

    int n;
    cin >> n;
    n++;
    // khai báo ma trận kề
    int **arr = new int *[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = new int[n];
        for (int j = 0; j < n; j++)
            arr[i][j] = 0;
    }

    // nhập các cạnh vào ma trận kề
    int a, b;
    while (cin >> a >> b)
    {
        arr[a][b] = 1;
        arr[b][a] = 1;
    }

    // khai báo distCounted - đánh dấu đã đếm khoảng cách giữa 2 đỉnh bất kỳ chưa
    bool **distCounted = new bool *[n];
    for (int i = 0; i < n; i++)
    {
        distCounted[i] = new bool[n];
        for (int j = 0; j < n; j++)
            distCounted[i][j] = false;
    }

    // tính chiều rộng cây bằng cách sử dụng hàm BFS từ mọi đỉnh
    int treeWidth = 0;
    for (int i = 1; i < n; i++)
        treeWidth += BFS(arr, n, i, distCounted);
    cout << treeWidth;

    // free arr
    for (int i = 0; i < n; i++)
        delete[] arr[i];
    delete[] arr;
    // free countedEdge
    for (int i = 0; i < n; i++)
        delete[] distCounted[i];
    delete[] distCounted;

    return 0;
}