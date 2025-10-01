import sys
input = sys.stdin.readline
n = int(input())

to = [[] for i in range(n+1)]
fromm = [[] for i in range(n+1)]

for i in range(1,n+1):
    a,b = map(int,input().split())
    to[i].extend([a,b])
    fromm[a].append(i)
    fromm[b].append(i)

def check(n,num):
    visited = [False] * (n+1)
