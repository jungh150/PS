from sys import stdin

t = int(stdin.readline())
for i in range(t):
    n = int(stdin.readline())
    div = n % 100
    if (n + 1) % div == 0:
        print("Good")
    else:
        print("Bye")