import sys

while True :
    a, b, c = map(int, sys.stdin.readline().split())

    if a + b + c == 0 :
        exit()

    max = c

    if a > max :
        max = a
    if b > max :
        max = b

    if a*a + b*b + c*c == max*max*2 :
        print("right")
    else :
        print("wrong")