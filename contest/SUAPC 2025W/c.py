from collections import deque
import sys
input = sys.stdin.readline
n = int(input())
print(10**100)
lst = list(map(int,input().split()))
q = deque(lst)
m = int(input())
num = list(input())
cnt = 0
q.popleft()
while q:
    for i in num:
        if i == 'D':
            if q[0] == -1:
                q.popleft()
        if i == 'A':
            if q[0] > 0 :
                q[0] = q[0] - 1
        if i == "J":
            if q[0] == 0:
                q.popleft()
        cnt += 1
    if cnt == 10**100:
        break
if q:
    print("NO")
else:
    print("YES")
 