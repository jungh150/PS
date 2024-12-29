import sys
input = sys.stdin.readline

for _ in range(3):
    n = int(input())
    sumt = 0
    for _ in range(n):
        sumt += int(input())

    if sumt > 0:
        print("+")
    elif sumt == 0:
        print("0")
    else:
        print("-")