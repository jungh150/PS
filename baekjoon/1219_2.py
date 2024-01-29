import sys

input = sys.stdin.readline
Min = sys.maxsize * -1
from collections import deque

Q = deque()
N, S, E, M = map(int, input().split())
isVisited = [False for i in range(N)]
Edges = []
for i in range(M):
    start, end, price = map(int, input().split())
    Edges.append((start, end, price))
CityMoney = list(map(int, input().split()))
Result = [Min for i in range(N)]
Result[S] = CityMoney[S]
Exist_Cylce = False
isgee = False


def BFS(x):
    Q.append(x)
    isVisited[x] = True
    while Q:
        now = Q.popleft()
        for start, end, price in Edges:
            if start == now and isVisited[end] == False:
                isVisited[end] = True
                Q.append(end)
    if isVisited[E]:
        return True
    else:
        return False


for _ in range(N - 1):
    for start, end, price in Edges:
        if Result[start] != Min and Result[end] < Result[start] - price + CityMoney[end]:
            Result[end] = Result[start] - price + CityMoney[end]

for start, end, price in Edges:
    if Result[start] != Min and Result[end] < Result[start] - price + CityMoney[end] and N != 1:
        Result[end] = Result[start] - price + CityMoney[end]
        Exist_Cylce = True
        if Exist_Cylce and BFS(end):
            isgee = True

if N == 1:
    if price >= CityMoney[E]:
        print(CityMoney[E])
    else:
        print("Gee")
else:
    if Result[E] == Min:
        print("gg")
    elif isgee:
        print("Gee")
    else:
        print(Result[E])
    