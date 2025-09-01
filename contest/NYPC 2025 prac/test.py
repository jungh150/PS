# ================================================================
# Game – Fast depth-4 αβ minimax with selective candidate pruning
# (NumPy removed for PyPy compatibility)
# ================================================================
class Game:
    R, C = 10, 17
    ME, OPP, NONE = 1, 2, 0

    def __init__(self, board, first):
        self.board = [row[:] for row in board]                # 10×17  int
        self.owner = [[0] * self.C for _ in range(self.R)]    # 10×17  0/1/2
        self.first = first
        self.turn = 0
        self.passed = False

    # ────────────────────────────────────────────────────────────
    # Helpers for in-place do / undo
    # ────────────────────────────────────────────────────────────
    def _do(self, mv, side):
        r1, c1, r2, c2 = mv
        if r1 == -1:
            return 0, []  # pass
        changed = []
        foe = self.OPP if side == self.ME else self.ME
        delta = 0
        for r in range(r1, r2 + 1):
            row_b = self.board[r]
            row_o = self.owner[r]
            for c in range(c1, c2 + 1):
                old_o = row_o[c]
                old_b = row_b[c]
                changed.append((r, c, old_o, old_b))
                if old_o == side:
                    pass
                elif old_o == foe:
                    delta += 2 if side == self.ME else -2
                else:
                    delta += 1 if side == self.ME else -1
                row_o[c] = side
                row_b[c] = 0
        return delta, changed

    def _undo(self, changed):
        for r, c, old_o, old_b in changed:
            self.owner[r][c] = old_o
            self.board[r][c] = old_b

    # ────────────────────────────────────────────────────────────
    # Enumerate candidate rectangles (optionally include gain-0 blockers)
    # Returns list of (gain, area, (r1,c1,r2,c2)) sorted by |gain|↓, area↓
    # ────────────────────────────────────────────────────────────
    def _edge_empty(self, r1, c1, r2, c2):
        if sum(self.board[r1][c1:c2 + 1]) == 0:
            return True
        if sum(self.board[r2][c1:c2 + 1]) == 0:
            return True
        if sum(self.board[r][c1] for r in range(r1, r2 + 1)) == 0:
            return True
        if sum(self.board[r][c2] for r in range(r1, r2 + 1)) == 0:
            return True
        return False

    def _rect_gain(self, r1, c1, r2, c2, side):
        foe = self.OPP if side == self.ME else self.ME
        take_foe = take_none = 0
        for r in range(r1, r2 + 1):
            for c in range(c1, c2 + 1):
                o = self.owner[r][c]
                if o == foe:
                    take_foe += 1
                elif o == self.NONE:
                    take_none += 1
        sign2 = 2 if side == self.ME else -2
        sign1 = 1 if side == self.ME else -1
        return sign2 * take_foe + sign1 * take_none

    def _opp_future_gain(self, r1, c1, r2, c2):
        take_me = take_none = 0
        for r in range(r1, r2 + 1):
            for c in range(c1, c2 + 1):
                o = self.owner[r][c]
                if o == self.ME:
                    take_me += 1
                elif o == self.NONE:
                    take_none += 1
        return -2 * take_me - take_none

    def _gen_moves(self, side, need_block=False):
        foe = self.OPP if side == self.ME else self.ME
        moves = []

        # 후반 판단 기준: 이미 점령된 셀이 130개 이상이면 후반
        total_owned = sum(o != self.NONE for row in self.owner for o in row)
        is_late_game = total_owned >= 130

        opp_best_gain = 0
        if need_block:
            for r1 in range(self.R):
                col = [0] * self.C
                for r2 in range(r1, self.R):
                    for c in range(self.C):
                        col[c] += self.board[r2][c]
                    rect = 0
                    for c1 in range(self.C):
                        rect = 0
                        for c2 in range(c1, self.C):
                            rect += col[c2]
                            if rect > 10:
                                break
                            if rect != 10:
                                continue
                            if self._edge_empty(r1, c1, r2, c2):
                                continue
                            g = self._opp_future_gain(r1, c1, r2, c2)
                            opp_best_gain = max(opp_best_gain, abs(g))

        for r1 in range(self.R):
            col_sum = [0] * self.C
            for r2 in range(r1, self.R):
                for c in range(self.C):
                    col_sum[c] += self.board[r2][c]
                for c1 in range(self.C):
                    if sum(self.board[r][c1] for r in range(r1, r2 + 1)) == 0:
                        continue
                    rect = 0
                    for c2 in range(c1, self.C):
                        rect += col_sum[c2]
                        if rect > 10:
                            break
                        if rect != 10:
                            continue
                        if self._edge_empty(r1, c1, r2, c2):
                            continue
                        gain = self._rect_gain(r1, c1, r2, c2, side)

                        # ⭐ 후반에는 gain ≤ 1 수 제거 (단, need_block이면 조건 완화)
                        if is_late_game and abs(gain) <= 1 and not need_block:
                            continue

                        keep = abs(gain) >= 1
                        if not keep and need_block:
                            future = self._opp_future_gain(r1, c1, r2, c2)
                            keep = (opp_best_gain - abs(future)) >= 2
                        if keep:
                            area = (r2 - r1 + 1) * (c2 - c1 + 1)
                            moves.append((gain, area, (r1, c1, r2, c2)))

        moves.sort(key=lambda x: (-abs(x[0]), -x[1]))
        return moves

    # ────────────────────────────────────────────────────────────
    # depth-limited α-β search (depth≤4)
    # ────────────────────────────────────────────────────────────
    def _ab(self, depth, side, diff, alpha, beta):
        if depth == 0:
            return diff
        maximizing = side == self.ME
        if depth == 3:
            moves = self._gen_moves(side, need_block=True)[:30+self.turn//15*2]
        elif depth == 2 or depth == 1:
            moves = self._gen_moves(side)[:10+self.turn//15*3]
        else:
            moves = []
        moves.append((0, 0, (-1, -1, -1, -1)))  # pass

        for gain, _area, mv in moves:
            delta, changed = self._do(mv, side)
            val = self._ab(depth - 1,
                           self.OPP if side == self.ME else self.ME,
                           diff + delta, alpha, beta)
            self._undo(changed)

            if maximizing:
                if val > alpha:
                    alpha = val
            else:
                if val < beta:
                    beta = val
            if beta <= alpha:
                break
        return alpha if maximizing else beta

    # ==========================================================
    # PUBLIC: decide my move
    # ==========================================================
    def _cur_diff(self):
        return sum(
            1 if o == self.ME else -1 if o == self.OPP else 0
            for row in self.owner for o in row
        )

    def calculateMove(self, _myTime, _oppTime):
        cur_diff = self._cur_diff()
        if cur_diff > 0 and self.passed:
            return (-1, -1, -1, -1)
        best_val = -10**9
        best_mv = (-1, -1, -1, -1)
        alpha, beta = -10**9, 10**9

        root_moves = self._gen_moves(self.ME)
        if cur_diff >= 0:root_moves.append((0, 0, (-1, -1, -1, -1)))
        for gain, _area, mv in root_moves:
            delta, changed = self._do(mv, self.ME)
            val = self._ab(3+self.turn//15*2, self.OPP, cur_diff + delta, alpha, beta)
            self._undo(changed)
            if val > best_val:
                best_val = val
                best_mv = mv
            if val > alpha:
                alpha = val
        return best_mv

    # ==========================================================
    # External board update helpers
    # ==========================================================
    def updateMove(self, r1, c1, r2, c2, isMyMove):
        if r1 == c1 == r2 == c2 == -1:
            self.passed = True
            return
        side = self.ME if isMyMove else self.OPP
        for r in range(r1, r2 + 1):
            for c in range(c1, c2 + 1):
                self.owner[r][c] = side
                self.board[r][c] = 0
        self.passed = False

    def updateOpponentAction(self, mv, _t):
        self.updateMove(*mv, isMyMove=False)

# ================================================================
# I/O Driver
# ================================================================
def main():
    while True:
        line = input().split()
        if not line:
            continue
        command, *param = line
        if command == "READY":
            first = param[0] == "FIRST"
            global game
            game_first = first
            print("OK", flush=True)
        elif command == "INIT":
            board = [list(map(int, row)) for row in param]
            game = Game(board, game_first)
        elif command == "TIME":
            game.turn += 2
            my_t, opp_t = map(int, param)
            mv = game.calculateMove(my_t, opp_t)
            game.updateMove(*mv, True)
            print(*mv, flush=True)
        elif command == "OPP":
            r1, c1, r2, c2, t = map(int, param)
            game.updateOpponentAction((r1, c1, r2, c2), t)
        elif command == "FINISH":
            break
        else:
            raise ValueError(f"Invalid command {command}")

if __name__ == "__main__":
    main()
