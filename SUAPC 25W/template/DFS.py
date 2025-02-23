def dfs(graph, node, visited):
    visited.add(node)
    print(node, end=" ")
    for neighbor in graph[node]:
        if neighbor not in visited:
            dfs(graph, neighbor, visited)



def dfs_stack(graph, start):
    stack = [start]
    visited = set()

    while stack:
        node = stack.pop()
        if node not in visited:
            print(node, end=" ")
            visited.add(node)
            stack.extend(graph[node][::-1])  # 역순 추가 (스택이므로)


###############

import queue
from sys import stdin
N,M,V = map(int,stdin.readline().split()) #노드 / 간선 / 시작점
# 인접 노드 리스트 ( 노드 개수만큼 )+1(계산쉽)
Nlist = [[] for _ in range(N+1)]

#인접노드정보받기
for _ in range(M):
    A,B = map(int,stdin.readline().split())
    Nlist[A].append(B)
    Nlist[B].append(A)

# 번호가 같은 노드부터 방문하기 위해 정렬
for i in range(N+1):
    Nlist[i].sort()

#DFS
visited = [False for _ in range(N+1)] # 방문 체크 리스트!

def DFS(v):
    print(v, end=" ") #방문하는 노드 차례대로 출력
    visited[v] = True
    for i in Nlist[v]:
        if not visited[i]:
            DFS(i) #재귀이용
DFS(V)