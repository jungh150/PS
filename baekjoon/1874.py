from sys import stdin

n = int(stdin.readline())
data = []
stk = []
ans = []

for _ in range(n):
    data.append(int(stdin.readline()))

i = 0
for j in range(1, n+1):
    stk.append(j)
    ans.append("+")
    while (data[i] == stk[-1]):
        stk.pop()
        ans.append("-")
        i += 1
        if len(stk) == 0:
            break

if len(stk) == 0:
    for i in ans:
        print(i)
else:
    print("NO")