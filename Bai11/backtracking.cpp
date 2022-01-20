#include <iostream>
#include <vector>
#include <fstream>

#define vb vector<bool>
#define pii pair<int, int>
#define vpii vector<pii>

using namespace std;

int k, m, n, ans;
vpii data(1e3);

void divide_cluster(vpii chosen_data, vb &check, int i)
{
    if (i == n)
    {
        int total = 0;

        for (int j = 0; j < m + n; ++j)
            total += (check[j] ? chosen_data[j].first : chosen_data[j].second);

        ans = max(ans, total);
        return;
    }

    for (int j = 0; j < m + n; ++j)
        if (!check[j])
        {
            check[j] = true;
            // continue to divide the cluster from i + 1
            divide_cluster(chosen_data, check, i + 1);
            check[j] = false;
        }
}

void backtracking(vb &visited, vpii &chosen_data, int i)
{
    if (i >= m + n)
    {
        vb check(m + n, false);
        divide_cluster(chosen_data, check, 0);
        return;
    }
    for (int j = 0; j < k; ++j)
    {
        if (!visited[j])
        {
            visited[j] = true;
            chosen_data.push_back(data[j]);
            // continue backtracking from i + 1
            backtracking(visited, chosen_data, i + 1);
            chosen_data.pop_back();
            visited[j] = false;
        }
    }
}

int main()
{
    // space complexity: O(n)
    // time complexity: O(k^(m+n) * (m+n)^n)

    ifstream file;
    file.open("input.txt");

    if (!file.is_open())
    {
        cout << "File not found!" << endl;
        return 0;
    }

    // read data
    file >> k >> n >> m;
    for (int i = 0; i < k; ++i)
        file >> data[i].first >> data[i].second;

    ans = 0;
    vb visited(k, false);
    vpii chosen_data;

    // backtracking to find maximun result
    backtracking(visited, chosen_data, 0);

    cout << "\nResult:\n";
    cout << ans;
    return 0;
}