import sys

n = int(sys.stdin.readline())
count = 0

for i in range(1, n+1) :
    isH = True

    num1 = i % 10
    newNum = i // 10
    num2 = newNum % 10
    dis = num1 - num2

    while True :
        num1 = newNum % 10
        newNum = newNum // 10
        if newNum == 0 :
            break
        num2 = newNum % 10
        if dis != (num1 - num2) :
            isH = False

    if isH :
        count += 1

print(count)