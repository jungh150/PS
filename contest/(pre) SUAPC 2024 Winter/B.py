from sys import stdin

t = int(stdin.readline())

if t == 1:
    a, b = map(int, stdin.readline().split())
    n = a + b
    i = 0
    res = ['a'] * 13
    while n > 0:
        rem = n % 26
        res[i] = chr(rem + 97)
        i += 1
        n = n // 26
    res = ''.join(res)
    print(res)
elif t == 2:
    input = stdin.readline().strip()
    i = 0
    res = 0
    for x in input:
        res += (ord(x) - 97) * pow(26, i)
        i += 1
    print(res)