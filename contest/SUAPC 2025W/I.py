from collections import deque
import sys
input = sys.stdin.readline
n = int(input())
lst = [[] for i in range(n+1)]
job = list(map(int,input().split()))
q = deque(job)
for i in range(2,n+1):
     lst[i].append(q.popleft())
for i in range(int(input())):
     cnt = 1
     dp = [0] * (n+1)
     a,b = map(int,input().split())
     for i in range(a,b+1):
          dp[i] = 1
     for i in range(b,a-1,-1):
        if dp[lst[i]] == 0:
            cnt += 1
     print(cnt)
# lst = [[] for i in range(n+1)]
# visited = [False] * (n+1)
# for i in range(2,n+1):
#     lst[i].append(q.popleft())
# def hamsu(num,range,cnt):
#     if visited[num] == True:
#         return cnt
#     visited[num] = True
#     if lst[n] in range:
#         hamsu(lst[n],range,cnt)
#     else:
#         return cnt + 1
# count = 0
# for i in range(int(input())):
#     a,b = map(int,input().split())
#     for j in range(b,a-1,-1):
#         count = hamsu(i,[_ for _ in range(1,b+1)],count)
#     print(count)