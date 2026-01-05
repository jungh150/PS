import sys
from queue import PriorityQueue
input = sys.stdin.readline

mod = 10 ** 9 + 7

def solve():
    ans = 1

    n = int(input())
    q = PriorityQueue()

    a = list(map(int, input().split()))
    for x in a:
        q.put(x)

    while q.qsize() >= 2:
        x = q.get()
        y = q.get()
        tmp = x * y
        q.put(tmp)
        tmp = tmp % mod
        ans = (ans * tmp) % mod

    print(ans)

T = int(input())
for i in range(T):
    solve()