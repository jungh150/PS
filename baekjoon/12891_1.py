from sys import stdin

s, p = map(int, stdin.readline().split())
data = stdin.readline().strip()

chk = list(map(int, stdin.readline().split()))
cur = [0] * 4
cnt = 0
start = 0

for i in range(0, p):
    if data[i] == 'A':
        cur[0] += 1
    elif data[i] == 'C':
        cur[1] += 1
    elif data[i] == 'G':
        cur[2] += 1
    elif data[i] == 'T':
        cur[3] += 1
    
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
    
    if data[start] == 'A':
        cur[0] -= 1
    elif data[start] == 'C':
        cur[1] -= 1
    elif data[start] == 'G':
        cur[2] -= 1
    elif data[start] == 'T':
        cur[3] -= 1

    if data[start+p] == 'A':
        cur[0] += 1
    elif data[start+p] == 'C':
        cur[1] += 1
    elif data[start+p] == 'G':
        cur[2] += 1
    elif data[start+p] == 'T':
        cur[3] += 1

    start += 1

print(cnt)