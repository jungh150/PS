import sys
input = sys.stdin.readline

N = int(input())

level_num = list(map(int,input().split()))

numBox = [[],[],[],[],[]]
for _ in range(N):
    a,b = map(int,input().split())
    numBox[a-1].append(b)

result = 60 * 4
for i in range(5):
    num_level = sorted(numBox[i])
    for j in range(level_num[i]-1):
        result += num_level[j]
        result += (num_level[j+1]-num_level[j])
        gap = num_level[j]
    result += num_level[level_num[i]-1]
print(result)