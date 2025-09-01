import heapq

def dijkstra(graph, start):
    INF = float('inf')
    dist = {node: INF for node in graph}
    dist[start] = 0
    pq = [(0, start)]

    while pq:
        curr_dist, node = heapq.heappop(pq)
        if curr_dist > dist[node]:
            continue
        for neighbor, weight in graph[node]:
            distance = curr_dist + weight
            if distance < dist[neighbor]:
                dist[neighbor] = distance
                heapq.heappush(pq, (distance, neighbor))

    return dist
