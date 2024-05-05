import sys
input = sys.stdin.readline

def LCSlength(x, y, m, n):
    b = [[0 for _ in range(n + 1)] for _ in range(m + 1)] # 테이블 b 선언 및 초기화
    c = [[0 for _ in range(n + 1)] for _ in range(m + 1)] # 테이블 c 선언 및 초기화

    for i in range(1, m + 1): # i : 행을 나타내는 변수
        for j in range(1, n + 1): # j : 열을 나타내는 변수
            if x[i - 1] == y[j - 1]: # X의 i번째 문자와 Y의 j번째 문자가 같을 때
                c[i][j] = c[i - 1][j - 1] + 1 # 대각선의 값 + 1
                b[i][j] = '↖'
            else: # X의 i번째 문자와 Y의 j번째 문자가 같지 않을 때
                if c[i - 1][j] >= c[i][j - 1]: # 위쪽의 값이 더 클 경우
                    c[i][j] = c[i - 1][j] # 위쪽의 값을 그대로
                    b[i][j] = '↑'
                else: # 왼쪽의 값이 더 클 경우
                    c[i][j] = c[i][j - 1] # 왼쪽의 값을 그대로
                    b[i][j] = '←'

    return b, c

def printLCS(b, x, i, j):
    if i == 0 or j == 0: # 테이블의 끝에 도달하면 종료
        return
    if b[i][j] == '↖':
        printLCS(b, x, i - 1, j - 1) # 대각선 칸으로 이동
        print(x[i - 1], end = ' ') # 출력 (x[i - 1] == y[j - 1])
    elif b[i][j] == '↑':
        printLCS(b, x, i - 1, j) # 위쪽 칸으로 이동
    else:
        printLCS(b, x, i, j - 1) # 왼쪽 칸으로 이동

x = ''.join(input().split()) # 공백을 기준으로 나누어서 문자열로 저장
y = ''.join(input().split()) # 공백을 기준으로 나누어서 문자열로 저장
m = len(x) # m : X의 길이
n = len(y) # n : Y의 길이

b, c = LCSlength(x, y, m, n)

print("length of LCS :", c[m][n]) # length of longest common subsequence
print("LCS : ", end = '')
printLCS(b, x, m, n) # longest common subsequence