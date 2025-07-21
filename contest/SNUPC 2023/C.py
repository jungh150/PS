from sys import stdin

n = int(stdin.readline())
data = stdin.readline().strip()

i = 0
ans = []

while i <= n:
    if data[i] == "S":
        ans.append("S")
        i += 1
        if data[i] == "N":
            i += 1
        