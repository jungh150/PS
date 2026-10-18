
# ================================
# Game 클래스: 게임 상태 관리
# ================================
class Game:
    ME, OPP, NONE = 1, 2, 0

    def __init__(self, board, first):
        self.board = board                    # 남아 있는 버섯 숫자
        self.first = first                    # 선공 여부(쓰지 않아도 무방)
        self.owner = [[self.NONE]*17 for _ in range(10)]  # 각 칸 소유 정보
        self.passed = False                   # 직전 턴 패스 여부

    # 사각형 (r1,c1)~(r2,c2) 이 유효한지?
    def isValid(self, r1, c1, r2, c2):
        s = 0
        r1fit = r2fit = c1fit = c2fit = False
        for r in range(r1, r2+1):
            for c in range(c1, c2+1):
                if self.board[r][c] != 0:
                    s += self.board[r][c]
                    if r == r1: r1fit = True
                    if r == r2: r2fit = True
                    if c == c1: c1fit = True
                    if c == c2: c2fit = True
        return s == 10 and r1fit and r2fit and c1fit and c2fit

    # ================================================================
    # 내 차례: 최대 득점(순득점) 직사각형 선택
    #   +2 : 상대 칸을 빼앗는 셀
    #   +1 : 무소유 셀을 새로 차지
    #   +0 : 이미 내 셀
    # ================================================================
    def calculateMove(self, _myTime, _oppTime):

        R, C = 10, 17
        ME, OP, NO = self.ME, self.OPP, self.NONE

        # ---------------- prefix-sum ----------------
        def build_ps(board):
            ps = [[0] * (C + 1) for _ in range(R + 1)]
            for r in range(R):
                acc = 0
                for c in range(C):
                    acc += board[r][c]
                    ps[r + 1][c + 1] = ps[r][c + 1] + acc
            return ps

        def rect_sum(ps, r1, c1, r2, c2):
            return (ps[r2 + 1][c2 + 1] - ps[r1][c2 + 1]
                    - ps[r2 + 1][c1] + ps[r1][c1])

        # 사각형 네 변에 버섯 존재?
        def borders_filled(board, r1, c1, r2, c2):
            top = any(board[r1][c] for c in range(c1, c2 + 1))
            bot = any(board[r2][c] for c in range(c1, c2 + 1))
            lef = any(board[r][c1] for r in range(r1, r2 + 1))
            rig = any(board[r][c2] for r in range(r1, r2 + 1))
            return top and bot and lef and rig

        # -------------------------------------------------------------

        # 내/상대 칸 수
        my_cnt = sum(row.count(ME) for row in self.owner)
        opp_cnt = sum(row.count(OP) for row in self.owner)
        cur_diff = my_cnt - opp_cnt

        # 내/상대 gain 계산
        def gain(owner, r1, c1, r2, c2, side):
            g = 0
            if side == ME:
                for r in range(r1, r2 + 1):
                    for c in range(c1, c2 + 1):
                        o = owner[r][c]
                        if o == OP:
                            g += 2
                        elif o == NO:
                            g += 1
            else:  # side == OP
                for r in range(r1, r2 + 1):
                    for c in range(c1, c2 + 1):
                        o = owner[r][c]
                        if o == ME:
                            g += 2
                        elif o == NO:
                            g += 1
            return g

        # -------------------------------------------------------------
        # 현재 보드에서 가능한 모든 직사각형과 gain 목록 (side 지정)
        # -------------------------------------------------------------
        def all_moves(board, owner, side):
            ps = build_ps(board)
            moves = []
            for r1 in range(R):
                for r2 in range(r1, R):
                    for c1 in range(C):
                        for c2 in range(c1, C):
                            if rect_sum(ps, r1, c1, r2, c2) != 10:
                                continue
                            if not borders_filled(board, r1, c1, r2, c2):
                                continue
                            g = gain(owner, r1, c1, r2, c2, side)
                            if g > 0:  # 득점 없는 수는 의미 없음
                                moves.append((g, (r1, c1, r2, c2)))
            return moves  # [(gain, move), …]

        # 현재 상태에서 상대가 즉시 두면 얻는 최대 gain (패스 가능성 포함)
        opp_moves_now = all_moves(self.board, self.owner, OP)
        opp_best_gain_now = max([g for g, _ in opp_moves_now], default=0)
        best_diff = cur_diff - opp_best_gain_now  # 내가 패스할 때 결과
        best_move = (-1, -1, -1, -1)  # 기본 = 패스

        # 내 모든 후보 수
        my_moves = all_moves(self.board, self.owner, ME)

        for my_gain, mv in my_moves:
            r1, c1, r2, c2 = mv

            # --------- 보드/소유 deep copy & 내 수 적용 ---------
            brd2 = [row[:] for row in self.board]
            own2 = [row[:] for row in self.owner]
            for r in range(r1, r2 + 1):
                for c in range(c1, c2 + 1):
                    brd2[r][c] = 0
                    own2[r][c] = ME
            # -----------------------------------------------

            # 상대가 두었을 때 최대 gain
            opp_moves = all_moves(brd2, own2, OP)
            opp_best = max([g for g, _ in opp_moves], default=0)

            final_diff = cur_diff + my_gain - opp_best

            if final_diff > best_diff:
                best_diff = final_diff
                best_move = mv

        return best_move

    # 상대 수 반영
    def updateOpponentAction(self, action, _time):
        self.updateMove(*action, isMyMove=False)

    # 보드·소유 정보를 실제로 갱신
    def updateMove(self, r1, c1, r2, c2, isMyMove):
        if r1 == c1 == r2 == c2 == -1:
            self.passed = True
            return

        new_owner = self.ME if isMyMove else self.OPP
        for r in range(r1, r2+1):
            for c in range(c1, c2+1):
                self.board[r][c] = 0          # 버섯 제거
                self.owner[r][c] = new_owner  # 소유권 이전
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
