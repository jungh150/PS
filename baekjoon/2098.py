import sys
input = sys.stdin.readline

n = int(input())
w = []

for _ in range(n):
    w.append(list(map(int, input().split())))

dp = [[0 for _ in range(1 << n)] for _ in range(n)]

def tsp(c, v):
    if v == (1 << n) - 1: # 모든 도시를 방문한 경우
        if w[c][0] == 0:
            return(sys.maxsize)
        else:
            return w[c][0]
    if dp[c][v] != 0: # 이미 방문한 도시인 경우
        return dp[c][v]
    
    mint = sys.maxsize
    for i in range(n):
        # 방문한 적이 없고, 갈 수 있는 도시인 경우
        if ((v & (1 << i)) == 0 and w[c][i] != 0):
            # 방문한 도시에 추가하여 다시 tsp 함수 호출
            mint = min(mint, tsp(i, (v | (1 << i))) + w[c][i])
    dp[c][v] = mint

    return dp[c][v]

print(tsp(0, 1)) # 1번 도시(인덱스 0)부터 시작한다고 가정