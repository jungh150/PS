from sys import stdin

n = int(stdin.readline())
sang = list(map(int, stdin.readline().split()))
m = int(stdin.readline())
card = list(map(int, stdin.readline().split()))

count = {}

for i in sang:
    if i in count:
        count[i] += 1
    else:
        count[i] = 1

for i in card:
    if i in count:
        print(count[i], end = " ")
    else:
        print(0, end = " ")