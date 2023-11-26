from sys import stdin

n = int(stdin.readline())
pos = []
neg = []
ans = 0
zero = False

for _ in range(n):
    x = int(stdin.readline())
    if x > 1:
        pos.append(x)
    elif x < 0:
        neg.append(x)
    elif x == 1:
        ans += 1
    else:
        zero = True

pos.sort(reverse=True)
neg.sort()

for i in range(0, len(pos), 2):
    if i + 1 < len(pos):
        ans += (pos[i] * pos[i+1])
    else:
        ans += pos[i]

for i in range(0, len(neg), 2):
    if i + 1 < len(neg):
        ans += (neg[i] * neg[i+1])
    else:
        if not zero:
            ans += neg[i]

print(ans)