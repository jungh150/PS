from sys import stdin

t = int(stdin.readline())

for _ in range(t):
    n, m = map(int, stdin.readline().split())
    A = list(map(int, stdin.readline().split()))
    B = list(map(int, stdin.readline().split()))
    count = 0

    A.sort()
    B.sort()

    j = 0
    for i in range(n):
        if j == m:
            j -= 1
        while B[j] < A[i]:
            j += 1
            if j >= m:
                break
        count += j

    print(count)