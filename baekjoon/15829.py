from sys import stdin

l = int(stdin.readline())
input = stdin.readline()
ans = 0
r = 31
m = 1234567891

for i in range(l):
    num = (ord(input[i]) - 96) * (r ** i)
    num = num % m
    ans = (ans + num) % m

print(ans)