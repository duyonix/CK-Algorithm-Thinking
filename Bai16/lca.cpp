#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node
{
    Node *left, *right;
    int key;
};

// Tạo 1 node mới
Node *createNode(int key)
{
    Node *temp = new Node;
    temp->key = key;
    temp->left = nullptr;
    temp->right = nullptr;
    return temp;
}

// hàm tìm Lowest Common Ancestor
Node *LCA(Node *root, int n1, int n2)
{
    if (root == NULL)
        return root;
    // nếu 1 trong 2 node là gốc của cây, thì LCA của 2 node là node gốc đó
    if (root->key == n1 || root->key == n2)
        return root;

    Node *left = LCA(root->left, n1, n2);   // ít nhất 1 node nằm lệch sang cây con trái
    Node *right = LCA(root->right, n1, n2); // ít nhất 1 node nằm lệch sang cây con phải

    // nếu 2 node n1, n2 nằm ở 2 bên cây con, thì LCA sẽ là gốc của cây hiện tại
    if (left != NULL && right != NULL)
        return root;
    // nếu n1, n2 đều không nằm ở cây con nào, suy ra n1, n2 không nằm trong cây hiện tại,
    // thì không có LCA của chúng trong cây này
    if (left == NULL && right == NULL)
        return NULL;

    // nếu cả 2 node n1, n2 đều nằm ở cây con trái thì ta tìm tiếp LCA của chúng trong cây con trái
    if (left != NULL)
        return LCA(root->left, n1, n2);
    // ngược lại
    return LCA(root->right, n1, n2);
}

/* Hàm tìm level của 1 node
 * Ý tưởng: mỗi lần đệ quy đi xuống dưới 2 cây con 1 lần, thì level tăng lên 1
 * khi tìm thấy node k thì level hiện tại sẽ là level của node k
 */
int findLevel(Node *root, int k, int level)
{
    if (root == NULL)
        return -1;
    if (root->key == k)
        return level;

    int left = findLevel(root->left, k, level + 1);
    if (left == -1)
        return findLevel(root->right, k, level + 1);
    return left;
}

/* Hàm tìm khoảng cách giữa 2 đỉnh
    Tìm LCA của 2 đỉnh đó, rồi cộng level so với LCA của 2 đỉnh đó lại
*/
int findDistance(Node *root, int a, int b)
{
    Node *lca = LCA(root, a, b);

    int d1 = findLevel(lca, a, 0);
    int d2 = findLevel(lca, b, 0);

    return d1 + d2;
}

/* Hàm xây dựng cây nhị phân từ 1 danh sách kề
   Ý tưởng: Bắt đầu từ 1 node đầu tiên làm root, ta BFS ra ngoài và gán lần lượt left right cho mỗi node đi qua
   Ta gán hàng xóm vừa tìm được cho left nếu left chưa có, còn left có rồi thì ta gán vào right
*/
Node *buildTreeFromAdjList(vector<vector<int>> adjList)
{
    queue<Node *> q;
    int n = adjList.size();
    Node *root = createNode(adjList[0][0]);
    q.push(root);

    while (!q.empty())
    {
        Node *u = q.front();
        q.pop();
        for (int i = 0; i < n; i++)
        {
            if (adjList[i][0] == u->key)
            {
                if (u->left == nullptr)
                {
                    u->left = createNode(adjList[i][1]);
                    q.push(u->left);
                }
                else
                {
                    u->right = createNode(adjList[i][1]);
                    q.push(u->right);
                }
            }
        }
    }

    return root;
}

int main()
{
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);

    int n;
    cin >> n;

    vector<vector<int>> adjList;
    int a, b;
    while (cin >> a >> b)
        adjList.push_back({a, b});
    Node *root = buildTreeFromAdjList(adjList);

    int treeWidth = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
            treeWidth += findDistance(root, i, j);
    }

    cout << treeWidth;

    return 0;
}