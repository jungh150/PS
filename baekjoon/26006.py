from sys import stdin

dr = [1, 1, 1, 0, 0, -1, -1, -1]
dc = [-1, 0, 1, -1, 1, -1, 0, 1]
n, k = map(int, stdin.readline().split())
wr, wc = map(int, stdin.readline().split())
br = []
bc = []

for _ in range(k):
    a, b = map(int, stdin.readline().split())
    br.append(a)
    bc.append(b)

nowAttacked = False
canAvoid = False

for i in range(k):
    if wr == br[i] or wc == bc[i] or wr - br[i] == wc - bc[i] or wr - br[i] == bc[i] - wc:
        nowAttacked = True
        break

cnt = 0
avail = 0
for i in range(8):
    if wr + dr[i] >= 1 and wr + dr[i] <= n and wc + dc[i] >= 1 and wc + dc[i] <= n:
        avail += 1
        for j in range(k):
            if wr + dr[i] == br[j] or wc + dc[i] == bc[j] or wr + dr[i] - br[j] == wc + dc[i] - bc[j] or wr + dr[i] - br[j] == bc[j] - wc - dc[i]:
                cnt += 1
                break
if cnt != avail:
    canAvoid = True

if nowAttacked and canAvoid:
    print("CHECK")
elif nowAttacked and not canAvoid:
    print("CHECKMATE")
elif not nowAttacked and not canAvoid:
    print("STALEMATE")
else:
    print("NONE")