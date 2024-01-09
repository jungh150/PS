from sys import stdin

word = stdin.readline()
cnt = 0

for x in word:
    print(x, end="")
    cnt += 1
    if cnt >= 10:
        cnt = 0
        print()