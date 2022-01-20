#include <iostream>
#include <queue>
using namespace std;

int BFS(bool **graph, int n, int start, bool **distCounted)
{
    bool *visited = new bool[n + 1]{false};

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
        for (int i = 1; i <= n; i++)
        {
            if (graph[u][i] && !visited[i])
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
    // khai báo ma trận kề
    bool **graph = new bool *[n + 1];
    for (int i = 1; i <= n; i++)
    {
        graph[i] = new bool[n + 1];
        for (int j = 1; j <= n; j++)
            graph[i][j] = false;
    }

    // nhập các cạnh vào ma trận kề
    int a, b;
    while (cin >> a >> b)
    {
        graph[a][b] = true;
        graph[b][a] = true;
    }

    // khai báo distCounted - đánh dấu đã đếm khoảng cách giữa 2 đỉnh bất kỳ chưa
    bool **distCounted = new bool *[n + 1];
    for (int i = 1; i <= n; i++)
    {
        distCounted[i] = new bool[n + 1];
        for (int j = 1; j <= n; j++)
            distCounted[i][j] = false;
    }

    // tính chiều rộng cây bằng cách sử dụng hàm BFS từ mọi đỉnh
    int treeWidth = 0;
    for (int i = 1; i <= n; i++)
        treeWidth += BFS(graph, n, i, distCounted);
    cout << treeWidth;

    // free arr
    for (int i = 1; i <= n; i++)
        delete[] graph[i];
    delete[] graph;
    // free distCounted
    for (int i = 1; i <= n; i++)
        delete[] distCounted[i];
    delete[] distCounted;

    return 0;
}