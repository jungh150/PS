# ================================
# Game 클래스: 게임 상태 관리
# ================================
class Game:

    def __init__(self, board, first):
        self.board = board            # 게임 보드 (2차원 배열)
        self.first = first            # 선공 여부
        self.passed = False           # 마지막 턴에 패스했는지 여부
        # 각 칸의 점령자 정보 저장 (None, "me", "opp")
        self.owner = [[None for _ in range(17)] for _ in range(10)]

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
        bestMove = (-1, -1, -1, -1)
        maxOpponentCells = -1
    
        for h in range(1, 4):
            for w in range(1, 4):
                for r1 in range(10 - h + 1):
                    for c1 in range(17 - w + 1):
                        r2 = r1 + h - 1
                        c2 = c1 + w - 1
                        if self.isValid(r1, c1, r2, c2):
                            opponentCells = sum(
                                1 for r in range(r1, r2+1) for c in range(c1, c2+1)
                                if self.owner[r][c] == "opp"
                            )
                            if opponentCells > maxOpponentCells:
                                maxOpponentCells = opponentCells
                                bestMove = (r1, c1, r2, c2)
    
        return bestMove if maxOpponentCells != -1 else (-1, -1, -1, -1)
    # =================== [필수 구현 끝] =============================

    # 상대방의 수를 받아 보드에 반영
    def updateOpponentAction(self, action, _time):
        self.updateMove(*action, False)

    # 주어진 수를 보드에 반영 (칸을 0으로 지움)
    def updateMove(self, r1, c1, r2, c2, isMyMove):
        if r1 == c1 == r2 == c2 == -1:
            self.passed = True
            return
        owner = "me" if isMyMove else "opp"
        for r in range(r1, r2 + 1):
            for c in range(c1, c2 + 1):
                self.board[r][c] = 0
                self.owner[r][c] = owner
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
