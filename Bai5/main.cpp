#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <map>
#include <iterator>

using namespace std;

void initialGraph(int **graph, int count)
{
    for (size_t i = 0; i < count; i++)
    {
        for (size_t j = 0; j < count; j++)
        {
            graph[i][j] = 0;
        }
    }
}
void readData(int &n, int &m, int &k, int **graph, map<int, int> q)
{
    fstream f;
    f.open("./input.txt", ios::in);
    f >> n >> m >> k;
    int u, v, nQue;
    graph = new int *[n];
    for (size_t i = 0; i < n; i++)
    {
        graph[i] = new int[n];
    }
    initialGraph(graph, n);
    for (size_t i = 0; i < m; i++)
    {
        f >> u >> v;
        graph[u - 1][v - 1] += 1;
    }
    f >> nQue;
    for (size_t i = 0; i < nQue; i++)
    {
        f >> u >> v;
        q.insert(pair<int, int>(u, v));
    }

    f.close();
}

void multiply(int **a, int **b, int n)
{
    // Creating an auxiliary matrix to store elements
    // of the multiplication matrix
    int mul[100][100];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mul[i][j] = 0;
            for (int k = 0; k < n; k++)
                mul[i][j] += a[i][k] * b[k][j];
        }
    }

    // Storing the multiplication result in a[][]
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = mul[i][j]; //Updating our matrix
}
void printMatrix(int **a, int n)
{
    for (int i = 0; i <= n - 1; i++)
    {
        for (int j = 0; j <= n - 1; j++)
        {

            cout << a[i][j] << "    ";
        }

        cout << endl;
    }
    cout << endl;
}
int main()
{
    int **Graph;
    int nVers, nEdges, nEdgesQueries;
    map<int, int> Queries;
    readData(nVers, nEdges, nEdgesQueries, Graph, Queries);
    //cout << Queries.size();
    for (size_t i = 0; i < nEdgesQueries - 1; i++)
    {
        multiply(Graph, Graph, nVers);
    }
    map<int, int>::iterator itr;
    for (itr = Queries.begin(); itr != Queries.end(); ++itr)
    {
        cout << Graph[itr->first][itr->second] << '\n';
    }
    return 1;
}