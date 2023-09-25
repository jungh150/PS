from sys import stdin

n, m = map(int, stdin.readline().split())

notHeard = []
notSeen = []

for _ in range(0, n):
    notHeard.append(stdin.readline().strip())

for _ in range(0, m):
    notSeen.append(stdin.readline().strip())

ansSet = (set(notHeard) & set(notSeen))
ans = sorted(list(ansSet))

print(len(ans))
for i in range(0, len(ans)):
    print(ans[i])