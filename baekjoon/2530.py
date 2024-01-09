from sys import stdin

h, m, s = map(int, stdin.readline().split())
time = int(stdin.readline())

s += time

if s >= 60:
    m += s // 60
    s = s % 60

if m >= 60:
    h += m // 60
    m = m % 60

if h >= 24:
    h = h % 24

print(h, m, s)