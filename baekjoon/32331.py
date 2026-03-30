import sys
input = sys.stdin.readline

n, m, x, y = map(int, input().split())
sn, h = map(int, input().split()) 

score = []

for _ in range(n - 1):
    a, b = input().split()
    if a[:4] == "2024":
        b = int(b)
        score.append(b + max(0, y - (x - b)))

score.sort(reverse=True)

if m - 1 >= len(score):
    print("YES")
    print(0)
    exit()

tmp = score[m - 1]
if tmp - h > y:
    print("NO")
else:
    print("YES")
    print(max(0, tmp - h))