from sys import stdin

n, p = map(int, stdin.readline().split())
stk = [[] for _ in range(6)]
count = 0

for _ in range(n):
    line, fret = map(int, stdin.readline().split())
    if len(stk[line-1]) == 0:
        stk[line-1].append(fret)
        count += 1
    else:
        if fret > stk[line-1][-1]:
            stk[line-1].append(fret)
            count += 1
        else:
            while fret < stk[line-1][-1]:
                stk[line-1].pop()
                count += 1
                if len(stk[line-1]) == 0:
                    break
            if len(stk[line-1]) == 0:
                stk[line-1].append(fret)
                count += 1
            elif fret > stk[line-1][-1]:
                stk[line-1].append(fret)
                count += 1

print(count)