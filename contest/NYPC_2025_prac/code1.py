# ================================
# Game 클래스: 게임 상태 관리
# ================================
class Game:

    def __init__(self, board, first):
        self.board = board            # 게임 보드 (2차원 배열)
        self.first = first            # 선공 여부
        self.passed = False           # 마지막 턴에 패스했는지 여부

    # 사각형 (r1, c1) ~ (r2, c2)이 유효한지 검사 (합이 10이고, 네 변을 모두 포함)
    def isValid(self, r1, c1, r2, c2):
        sums = 0
        r1fit = c1fit = r2fit = c2fit = False

        for r in range(r1, r2 + 1):
            for c in range(c1, c2 + 1):
                if self.board[r][c] != 0:
                    sums += self.board[r][c]
                    if r == r1:
                        r1fit = True
                    if r == r2:
                        r2fit = True
                    if c == c1:
                        c1fit = True
                    if c == c2:
                        c2fit = True
        return sums == 10 and r1fit and r2fit and c1fit and c2fit

    # ================================================================
    # ===================== [필수 구현] ===============================
    # 합이 10인 유효한 사각형을 찾아 (r1, c1, r2, c2) 튜플로 반환
    # 없으면 (-1, -1, -1, -1) 반환 (패스 의미)
    # ================================================================
    def calculateMove(self, _myTime, _oppTime):
        rows, cols = len(self.board), len(self.board[0])
        
        # 작은 사각형부터 큰 사각형 순서로 탐색
        for height in range(1, rows + 1):  # 세로 길이
            for width in range(1, cols + 1):  # 가로 길이
                for r1 in range(rows - height + 1):
                    for c1 in range(cols - width + 1):
                        r2 = r1 + height - 1
                        c2 = c1 + width - 1
                        if self.isValid(r1, c1, r2, c2):
                            return (r1, c1, r2, c2)
        return (-1, -1, -1, -1)
    # =================== [필수 구현 끝] =============================

    # 상대방의 수를 받아 보드에 반영
    def updateOpponentAction(self, action, _time):
        self.updateMove(*action, False)

    # 주어진 수를 보드에 반영 (칸을 0으로 지움)
    def updateMove(self, r1, c1, r2, c2, _isMyMove):
        if r1 == c1 == r2 == c2 == -1:
            self.passed = True
            return
        for r in range(r1, r2 + 1):
            for c in range(c1, c2 + 1):
                self.board[r][c] = 0
        self.passed = False


# ================================
# main(): 입출력 처리 및 게임 진행
# ================================
def main():
    while True:
        line = input().split()

        if len(line) == 0:
            continue

        command, *param = line

        if command == "READY":
            # 선공 여부 확인
            turn = param[0]
            global first
            first = turn == "FIRST"
            print("OK", flush=True)
            continue

        if command == "INIT":
            # 보드 초기화
            board = [list(map(int, row)) for row in param]
            global game
            game = Game(board, first)
            continue

        if command == "TIME":
            # 내 턴: 수 계산 및 실행
            myTime, oppTime = map(int, param)
            ret = game.calculateMove(myTime, oppTime)
            game.updateMove(*ret, True)
            print(*ret, flush=True)
            continue

        if command == "OPP":
            # 상대 턴 반영
            r1, c1, r2, c2, time = map(int, param)
            game.updateOpponentAction((r1, c1, r2, c2), time)
            continue

        if command == "FINISH":
            break

        assert False, f"Invalid command {command}"


if __name__ == "__main__":
    main()
