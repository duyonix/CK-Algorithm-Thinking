#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <fstream>

#define MAX (1e6 + 2)
#define pii pair<int, int>

using namespace std;

vector<int> color_layer(MAX, 0);

struct Segment
{
    int a, b, id;
};

bool compare(Segment x, Segment y)
{
    return x.a < y.a;
}

struct compare_pii
{
    bool operator()(pii const &x, pii const &y)
    {
        return (x.first > y.first) || (x.first == y.first && x.second > y.second);
    }
};

int main()
{
    // space complexity: O(n)
    // time complexity: O(nlog(n))

    ifstream file;
    file.open("input.txt");

    if (!file.is_open())
    {
        cout << "File not found!" << endl;
        return 0;
    }

    int n, max_layer = 0;
    file >> n;
    vector<Segment> segments(n);

    for (int i = 0; i < n; ++i)
    {
        segments[i].id = i;
        file >> segments[i].a >> segments[i].b;
        ++color_layer[segments[i].a];
        --color_layer[segments[i].b + 1];
    }

    file.close();

    for (int i = 1; i < MAX; ++i)
    {
        color_layer[i] += color_layer[i - 1];
        max_layer = max(max_layer, color_layer[i]);
    }

    cout << "\nResult:\n";
    cout << max_layer << endl;

    sort(segments.begin(), segments.end(), compare);
    vector<int> color_code(n);
    priority_queue<pii, vector<pii>, compare_pii> pq;

    for (int i = 0; i < max_layer; ++i)
        pq.push(pii(0, i + 1));

    for (int i = 0; i < n; ++i)
    {
        pii end_point = pq.top();
        pq.pop();
        color_code[segments[i].id] = end_point.second;
        pq.push(pii(segments[i].b, end_point.second));
    }

    for (int i = 0; i < n; ++i)
        cout << color_code[i] << " ";
    return 0;
}