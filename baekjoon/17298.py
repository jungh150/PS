from sys import stdin

n = int(stdin.readline())
data = list(map(int, stdin.readline().split()))
stk = []
oks = [0] * n

for i in range(0, n):
    while len(stk) != 0 and data[stk[-1]] < data[i]: 
        oks[stk.pop()] = data[i]
    stk.append(i)

while len(stk) > 0:
    oks[stk.pop()] = -1

for i in oks:
    print(i, end=" ")