from queue import PriorityQueue
import sys 

R, C = map(int, sys.stdin.readline().split())

table =[]
for _ in range(R):
    table.append(list(map(int, sys.stdin.readline().split())))

dx = [1,-1,0,0]
dy = [0,0,1,-1]

lst = [[] for i in range((R*C)+1)]

for i in range(R):
    for j in range(C):
        for k in range(4):
            next_x = j + dx[k]
            next_y = i + dy[k]
            if 0 <= next_x < C and 0<= next_y< R:
                lst[table[i][j]].append(table[next_y][next_x])
for i in range(R*C+1):
    lst[i].sort()

def find_dishes(temp):
    tempdish = temp
    dist = lst[temp]
    this_dishes = 0
    for i in lst[temp]:
        if tempdish <= i :

    


# def find_dishes(r,c):
#     que = PriorityQueue()
#     this_dishes = 0
#     nowNum = table[r][c]
#     que.put((nowNum,r,c))

#     visited = [[False for _ in range(C)] for _ in range(R)]
#     visited[r][c] = True
    
#     while que.qsize() != 0:
#         now_values = que.get()
#         now_value = now_values[0]
#         a = now_values[1]
#         b = now_values[2]

#         if nowNum <= now_value:
#             nowNum = now_value
#             this_dishes+= 1

#             for i in range(4):
#                 next_a = a + dx[i]
#                 next_b = b + dy[i]
#                 if next_a >= 0 and next_a < R and next_b >= 0 and next_b < C and not visited[next_a][next_b]:
#                     que.put((table[next_a][next_b],next_a,next_b))
#                     visited[next_a][next_b] = True
        
#     return this_dishes


result = 0
for i in range(1,R*C+1):
    find_dishes(i)
print(result)