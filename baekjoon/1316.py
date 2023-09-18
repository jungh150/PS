from sys import stdin

n = int(stdin.readline())
count = 0

for i in range(0, n):
    str = stdin.readline().strip()
    alpha = [0] * 26
    isGroup = True

    alpha[ord(str[0])-97] = 1

    for j in range(1, len(str)):
        if str[j] != str[j-1]:
            if alpha[ord(str[j])-97] == 0:
                alpha[ord(str[j])-97] = 1
            else:
                isGroup = False
                break

    if isGroup:
        count += 1

print(count)