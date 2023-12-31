from sys import stdin

n = int(stdin.readline())
data = list(map(int, stdin.readline().split()))
lie = []
notLie = []
ans = []

for x in data:
    if x > 0:
        lie.append(x)
    else:
        notLie.append(-x)

lie.sort()
notLie.sort(reverse=True)

for i in range(n+1):
    lier = 0
    for j in range(len(lie)):
        if lie[j] > i:
            lier += len(lie) - j
            break
    for j in range(len(notLie)):
        if notLie[j] < i:
            lier += len(notLie) - j
            break
    if lier == i:
        ans.append(i)
    # for x in data:
    #     if x > 0:
    #         if x > i:
    #             lier += 1
    #     else:
    #         if -x < i:
    #             lier += 1
    #     if lier > i:
    #         break
    # if lier == i:
    #     ans.append(i)

print(len(ans))
for x in ans:
    print(x, end=" ")