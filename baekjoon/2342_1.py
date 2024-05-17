import sys
input = sys.stdin.readline

data = list(map(int, input().split()))
n = len(data) - 1
l = [0 for _ in range(n + 1)]
r = [0 for _ in range(n + 1)]
p = [0 for _ in range(n + 1)]

for i in range(n):
    if l[i] == data[i] or r[i] == data[i]:
        l[i + 1] = l[i]
        r[i + 1] = r[i]
        p[i + 1] = p[i] + 1
    elif l[i] == 0:
        l[i + 1] = data[i]
        r[i + 1] = r[i]
        p[i + 1] = p[i] + 2
    elif r[i] == 0:
        l[i + 1] = l[i]
        r[i + 1] = data[i]
        p[i + 1] = p[i] + 2
    else:
        ldif = abs(l[i] - data[i])
        if ldif == 3:
            ldif = 1
        rdif = abs(r[i] - data[i])
        if rdif == 3:
            rdif = 1
        if ldif < rdif:
            l[i + 1] = data[i]
            r[i + 1] = r[i]
            p[i + 1] = p[i] + ldif + 2
        else:
            l[i + 1] = l[i]
            r[i + 1] = data[i]
            p[i + 1] = p[i] + rdif + 2

print(p[n])