from sys import stdin

n, m = map(int, stdin.readline().split())

notHeard = []
notSeen = []
ans = []

for _ in range(0, n):
    notHeard.append(stdin.readline().strip())

for _ in range(0, m):
    notSeen.append(stdin.readline().strip())

notHeard = sorted(notHeard)
notSeen = sorted(notSeen)
hIndex = 0
sIndex = 0

while (hIndex < n) & (sIndex < m):
    if (notHeard[hIndex] == notSeen[sIndex]):
        ans.append(notHeard[hIndex])
        hIndex += 1
        sIndex += 1
    else:
        if (notHeard[hIndex] > notSeen[sIndex]):
            sIndex += 1
        else:
            hIndex += 1

print(len(ans))
for i in range(0, len(ans)):
    print(ans[i])