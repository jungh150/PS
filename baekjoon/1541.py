from sys import stdin

a = list(map(str, stdin.readline().split("-")))

def mySum(a):
    sum = 0
    tmp = list(map(int, a.split("+")))
    for i in tmp:
        sum += int(i)
    return sum

sum = mySum(a[0])

for i in range(1, len(a)):
    sum -= mySum(a[i])

print(sum)