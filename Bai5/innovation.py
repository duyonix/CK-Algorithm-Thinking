# import sympy library
from sympy import *


graph = []  # ma trận kề
edges = []  # Danh sách các cạnh (có đường đi). Vd: [u,v] => u đi tới v được
queries = []  # Những truy vấn, gồm cặp đỉnh (u,v)


def readData():
    iFile = open("input.txt", "r")
    data = iFile.readline()
    print(data.split())
    # Đọc data
    n, m, k = data.split()
    n = int(n)
    m = int(m)
    k = int(k)
    # Đọc m cạnh
    for i in range(0, m):
        temp = iFile.readline()
        edge = [int(x) for x in temp.split()]
        edges.append(edge)

    q = iFile.readline().split()
    q = int(q[0])
    # Đọc q truy vấn
    for i in range(0, q):
        temp = iFile.readline()
        query = [int(x) for x in temp.split()]
        queries.append(query)

    iFile.close()
    return n, m, k, q


def updateGraph(n):
    for i in range(0, n):  # Khởi tạo 0
        graph.append([0 for j in range(0, n)])
    for (
        edge
    ) in (
        edges
    ):  # Update ma trận kề, vì arr start tại 0 nên phải -1 để tới đỉnh tương ứng
        graph[edge[0] - 1][edge[1] - 1] += 1


n, m, k, q = readData()

updateGraph(n)

M = Matrix(graph)
# Tìm ma trận chuyển cơ sở P, ma trận chéo hoá D
P, D = M.diagonalize()
#  inverse of matrix P
P_inverse = P.inv()
print("Matrix : {} ".format(M))

# Use sympy.diagonalize() method
print("Diagonal of a matrix : {}".format(D))
print("P : {}".format(P))

# Calculate result: D^k
for i in range(0, n):
    D[i, i] = D[i, i] ** k

Result = P * D * P_inverse

print("Matrix result : {}".format(D))
# In kết quả
for i in range(0, q):
    print(
        "From vertex "
        + str(queries[i][0])
        + " to vertex "
        + str(queries[i][1])
        + " : "
        + str(Result[queries[i][0] - 1, queries[i][1] - 1])
        + " ways"
    )
