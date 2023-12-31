from sys import stdin

t = int(stdin.readline())
for i in range(t) :
    isGood = True
    n = int(stdin.readline())
    sum1 = 0
    for j in range(2, n // 2):
        if n % j == 0:
            sum1 += j
            print("sum1 =", sum1)
            sum2 = 0
            for k in range(2, j // 2):
                if j % k == 0:
                    sum2 += k
                    print("sum2 =", sum2)
            if sum2 > j:
                isGood = False
    if sum1 > n and isGood:
        print("Good Bye")
    else:
        print("BOJ 2022")