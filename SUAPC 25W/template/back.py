# 4️⃣ 백트래킹 (Backtracking)

# 모든 경우의 수를 탐색하면서 조건을 만족하는 경우만 선택하는 방법
# 대표적인 예제: N-Queen 문제

def solve_n_queens(n):
    board = [-1] * n
    solutions = []

    def is_safe(row, col):
        for r in range(row):
            if board[r] == col or abs(board[r] - col) == row - r:
                return False
        return True

    def backtrack(row):
        if row == n:
            solutions.append(board[:])
            return
        for col in range(n):
            if is_safe(row, col):
                board[row] = col
                backtrack(row + 1)
                board[row] = -1

    backtrack(0)
    return solutions