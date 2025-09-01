from collections import deque

def bfs(graph, start):
    q = deque([start])
    visited = set([start])

    while q:
        node = q.popleft()
        print(node, end=" ")
        for neighbor in graph[node]:
            if neighbor not in visited:
                visited.add(neighbor)
                q.append(neighbor)


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
    
#BFS
from collections import deque #큐 필요
visited = [False for _ in range(N+1)] # 방문 체크 리스트!

def BFS(v):
    Myqueue = deque()
    Myqueue.append(v)
    visited[v] = True
    while(Myqueue): # 마이큐에 값이 있을 때까지
        NowNode = Myqueue.popleft() #선입선출
        print(NowNode, end = " ")#방문하는 노드 차례대로 출력
        for i in Nlist[NowNode]:
            if not visited[i]:
                visited[i] = True
                Myqueue.append(i)
BFS(V)