import sys

a,b,c = map(int, sys.stdin.readline().split())

f= 0
s = 0

# f-s
dp= [[[ [-1 for _ in range(101)] for _ in range(101)] for _ in range(101)] for _ in range(30)]
def td(round, a, b, c):

    if dp[round][a][b][c] != -1:
        return dp[round][a][b][c]
    
    if a == 0 and  b== 0 and c == 0:
        dp[round][0][0][0] = 0
        return 0
    
    dp[round][a][b][c] = max(min(round,a) - td(round+1, a-min(round,a), b, c), min(round,b) - td(round+1, a, b-min(round,b), c), min(round,c) - td(round+1, a, b, c-min(round,c)))
    print(round, a, b, c)
    print(dp[round][a][b][c])
    return dp[round][a][b][c]

if (td(1, a, b, c) > 0):
    print("F")
elif (td(1, a, b, c) < 0):
    print("S")
else:
    print("D")
    

    

    
  

