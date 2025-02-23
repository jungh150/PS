# 5️⃣ 위상 정렬 (Topological Sort)

# 사이클이 없는 방향 그래프(DAG)에서 노드를 정렬하는 방법
# 주로 작업 스케줄링, 순서가 있는 작업 처리에 사용됨.
from collections import deque

def topological_sort(graph, n):
    in_degree = [0] * n
    for u in graph:
        for v in graph[u]:
            in_degree[v] += 1

    queue = deque([i for i in range(n) if in_degree[i] == 0])
    result = []

    while queue:
        node = queue.popleft()
        result.append(node)
        for neighbor in graph[node]:
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                queue.append(neighbor)

    return result if len(result) == n else "Cycle detected"