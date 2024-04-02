import sys
input = sys.stdin.readline

m = int(input()) # 조약돌 색 종류
color = list(map(int, input().split())) # 색 별 조약돌의 수
k = int(input()) # 뽑는 조약돌의 수
n = sum(color) # 전체 조약돌 수

ans = 0
for x in color:
    if x >= k:
        tmp = 1
        for i in range(k):
            tmp *= ((x - i) / (n - i))
        ans += tmp

print(ans)