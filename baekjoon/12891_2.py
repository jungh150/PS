from sys import stdin

def match(c):
    if c == 'A':
        return 0
    elif c == 'C':
        return 1
    elif c == 'G':
        return 2
    elif c == 'T':
        return 3
    else:
        return -1

s, p = map(int, stdin.readline().split())
data = stdin.readline().strip()

chk = list(map(int, stdin.readline().split()))
cur = [0] * 4
cnt = 0
start = 0

for i in range(0, p):
    cur[match(data[i])] += 1
    
while start+p <= s:
    isSafe = True
    for j in range(0, 4):
        if cur[j] < chk[j]:
            isSafe = False
            break
    if isSafe:
        cnt += 1

    if start+p == s:
        break
    
    cur[match(data[start])] -= 1
    cur[match(data[start+p])] += 1

    start += 1

print(cnt)