#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#define vb vector<bool>

using namespace std;

struct cluster
{
    int a, b, id;
};

bool compare_a(cluster x, cluster y)
{
    return x.a > y.a || (x.a == y.a && x.b < y.b);
}

bool compare_b(cluster x, cluster y)
{
    return x.b > y.b || (x.b == y.b && x.a < y.a);
}

// update check array to check if the segment is chosen for the cluster
void check_data(vb &check, vector<cluster> arr, int &index, int &remain)
{
    --remain;
    check[arr[index].id] = true;
    while (check[arr[index].id])
        ++index;
}

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

    // read data
    int k, m, n;
    file >> k >> n >> m;
    vector<cluster> cluster_a, cluster_b;
    for (int i = 0; i < k; ++i)
    {
        cluster temp;
        file >> temp.a >> temp.b;
        temp.id = i;
        cluster_a.push_back(temp);
        cluster_b.push_back(temp);
    }

    // sort for each cluster
    sort(cluster_a.begin(), cluster_a.end(), compare_a);
    sort(cluster_b.begin(), cluster_b.end(), compare_b);

    vector<bool> check(k, false);
    int ans = 0, i = 0, j = 0;
    while (n > 0 || m > 0)
    {
        if (m == 0) // cluster_b is full, we push in cluster_a until it's full
        {
            ans += cluster_a[i].a;
            check_data(check, cluster_a, i, n);
        }
        else if (n == 0) // cluster_a is full, we push in cluster_n until it's full
        {
            ans += cluster_b[j].b;
            check_data(check, cluster_b, j, m);
        }
        else
        {
            if (cluster_a[i].a > cluster_b[j].b ||
                (cluster_a[i].a == cluster_b[j].b && cluster_a[i].b < cluster_b[j].a))
            {
                // case for cluster_a
                ans += cluster_a[i].a;
                check_data(check, cluster_a, i, n);
            }
            else
            {
                // case for cluster_b
                ans += cluster_b[j].b;
                check_data(check, cluster_b, j, m);
            }
        }
    }
    cout << "\nResult:\n";
    cout << ans;
    return 0;
}