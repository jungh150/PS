import sys
input = sys.stdin.readline

str1 = input().strip()
str2 = input().strip()
len1 = len(str1)
len2 = len(str2)

dp = [[0 for _ in range(len2 + 1)] for _ in range(len1 + 1)]
memo = [[0 for _ in range(len2 + 1)] for _ in range(len1 + 1)]

for i in range(1, len1 + 1):
    for j in range(1, len2 + 1):
        if str1[i - 1] == str2[j - 1]:
            dp[i][j] = dp[i - 1][j - 1] + 1
            memo[i][j] = "↖"
        else:
            if dp[i - 1][j] >= dp[i][j - 1]:
                dp[i][j] = dp[i - 1][j]
                memo[i][j] = "↑"
            else:
                dp[i][j] = dp[i][j - 1]
                memo[i][j] = "←"

print(dp[len1][len2]) # LCS의 길이 출력

ans = ""
i = len1
j = len2
while i > 0 and j > 0:
    if memo[i][j] == "↖":
        ans  = ans + str1[i - 1]
        i -= 1
        j -= 1
    elif memo[i][j] == "↑":
        i -= 1
    else:
        j -= 1

# LCS 출력
for i in range(len(ans) - 1, -1, -1):
    print(ans[i], end = "")