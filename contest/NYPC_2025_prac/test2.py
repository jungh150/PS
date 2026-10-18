# ================================================================
# Game – αβ Minimax with branching based on first/second move
# ================================================================
class Game:
    R, C = 10, 17
    ME, OPP, NONE = 1, 2, 0

    def __init__(self, board, first):
        self.board = [row[:] for row in board]
        self.owner = [[0] * self.C for _ in range(self.R)]
        self.first = first
        self.turn = 0
        self.passed = False

    def _do(self, mv, side):
        r1, c1, r2, c2 = mv
        if r1 == -1:
            return 0, []
        changed = []
        foe = self.OPP if side == self.ME else self.ME
        delta = 0
        for r in range(r1, r2 + 1):
            for c in range(c1, c2 + 1):
                old_o = self.owner[r][c]
                old_b = self.board[r][c]
                changed.append((r, c, old_o, old_b))
                if old_o == side:
                    pass
                elif old_o == foe:
                    delta += 2 if side == self.ME else -2
                else:
                    delta += 1 if side == self.ME else -1
                self.owner[r][c] = side
                self.board[r][c] = 0
        return delta, changed

    def _undo(self, changed):
        for r, c, old_o, old_b in changed:
            self.owner[r][c] = old_o
            self.board[r][c] = old_b

    def _edge_empty(self, r1, c1, r2, c2):
        return (
            sum(self.board[r1][c1:c2 + 1]) == 0 or
            sum(self.board[r2][c1:c2 + 1]) == 0 or
            sum(self.board[r][c1] for r in range(r1, r2 + 1)) == 0 or
            sum(self.board[r][c2] for r in range(r1, r2 + 1)) == 0
        )

    def _rect_gain(self, r1, c1, r2, c2, side):
        foe = self.OPP if side == self.ME else self.ME
        take_foe = take_none = 0
        for r in range(r1, r2 + 1):
            for c in range(c1, c2 + 1):
                o = self.owner[r][c]
                if o == foe: take_foe += 1
                elif o == self.NONE: take_none += 1
        return (2 if side == self.ME else -2) * take_foe + (1 if side == self.ME else -1) * take_none

    def _opp_future_gain(self, r1, c1, r2, c2):
        take_me = take_none = 0
        for r in range(r1, r2 + 1):
            for c in range(c1, c2 + 1):
                o = self.owner[r][c]
                if o == self.ME: take_me += 1
                elif o == self.NONE: take_none += 1
        return -2 * take_me - take_none

    def _gen_moves(self, side, need_block=False):
        moves = []
        opp_best_gain = 0
        if need_block:
            for r1 in range(self.R):
                col = [0] * self.C
                for r2 in range(r1, self.R):
                    for c in range(self.C): col[c] += self.board[r2][c]
                    for c1 in range(self.C):
                        rect = 0
                        for c2 in range(c1, self.C):
                            rect += col[c2]
                            if rect > 10: break
                            if rect != 10: continue
                            if self._edge_empty(r1, c1, r2, c2): continue
                            g = self._opp_future_gain(r1, c1, r2, c2)
                            opp_best_gain = max(opp_best_gain, abs(g))

        for r1 in range(self.R):
            col_sum = [0] * self.C
            for r2 in range(r1, self.R):
                for c in range(self.C): col_sum[c] += self.board[r2][c]
                for c1 in range(self.C):
                    if sum(self.board[r][c1] for r in range(r1, r2 + 1)) == 0: continue
                    rect = 0
                    for c2 in range(c1, self.C):
                        rect += col_sum[c2]
                        if rect > 10: break
                        if rect != 10: continue
                        if self._edge_empty(r1, c1, r2, c2): continue
                        gain = self._rect_gain(r1, c1, r2, c2, side)
                        keep = abs(gain) >= 1
                        if not keep and need_block:
                            future = self._opp_future_gain(r1, c1, r2, c2)
                            keep = (opp_best_gain - abs(future)) >= 2
                        if keep:
                            area = (r2 - r1 + 1) * (c2 - c1 + 1)
                            moves.append((gain, area, (r1, c1, r2, c2)))
        moves.sort(key=lambda x: (-abs(x[0]), -x[1]))
        return moves

    def _ab(self, depth, side, diff, alpha, beta):
        if depth == 0:
            return diff
        maximizing = side == self.ME

        # First/Second Player: Different Search Breadth & Depth
        if self.first:
            if depth == 3:
                moves = self._gen_moves(side, need_block=True)[:30 + self.turn // 15 * 2]
            elif depth in [2, 1]:
                moves = self._gen_moves(side)[:10 + self.turn // 15 * 3]
            else:
                moves = []
        else:
            if depth == 3:
                moves = self._gen_moves(side, need_block=True)[:20]
            elif depth % 2 == 1:
                moves = self._gen_moves(side, need_block=True)[:5 + self.turn // 15 * 3]
            else:
                moves = self._gen_moves(side)[:5 + self.turn // 15 * 3]

        moves.append((0, 0, (-1, -1, -1, -1)))  # pass

        for gain, _area, mv in moves:
            delta, changed = self._do(mv, side)
            val = self._ab(depth - 1, self.OPP if side == self.ME else self.ME, diff + delta, alpha, beta)
            self._undo(changed)

            if maximizing:
                if val > alpha: alpha = val
            else:
                if val < beta: beta = val
            if beta <= alpha:
                break
        return alpha if maximizing else beta

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
        if cur_diff >= 0:
            root_moves.append((0, 0, (-1, -1, -1, -1)))

        depth = 3 + self.turn // 15 * 2 if self.first else 3
        for gain, _area, mv in root_moves:
            delta, changed = self._do(mv, self.ME)
            val = self._ab(depth, self.OPP, cur_diff + delta, alpha, beta)
            self._undo(changed)
            if val > best_val:
                best_val = val
                best_mv = mv
            if val > alpha:
                alpha = val
        return best_mv

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
