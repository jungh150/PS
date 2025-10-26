#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Ataxx-like 7x7 Judge
- Runs two agent executables that implement the protocol in the problem statement.
- Enforces time limits, validates moves, applies rules (division/leap + infection), logs everything.
- Produces a final result with score difference.

Usage:
  python judge.py --agent1 ./agent_v1 --agent2 ./sample --log game_log.txt --time 10000 --swap

Notes:
- agent1 starts as FIRST (O), agent2 as SECOND (X). With --swap, it will run two games swapping roles.
- Agents must flush after every line.
"""

import argparse, subprocess, threading, queue, time, os, sys, shlex, random
from dataclasses import dataclass, field
from typing import List, Tuple, Optional

N = 7
EMPTY='.'
O='O'
X='X'
DIR8 = [(-1,-1),(-1,0),(-1,1),(0,-1),(0,1),(1,-1),(1,0),(1,1)]

@dataclass
class Move:
    x1:int; y1:int; x2:int; y2:int; is_pass:bool=False

@dataclass
class AgentProc:
    path:str
    proc:subprocess.Popen
    out_queue:queue.Queue = field(default_factory=queue.Queue)
    reader_thread:threading.Thread = None
    alive:bool=True

def start_agent(path:str)->AgentProc:
    # Windows-friendly: use shell=False, pass as list if possible
    args = shlex.split(path) if os.name!='nt' else [path]
    proc = subprocess.Popen(args, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, bufsize=1, universal_newlines=True)
    ap = AgentProc(path=path, proc=proc)
    def reader():
        try:
            for line in proc.stdout:
                ap.out_queue.put(line.rstrip('\r\n'))
        except Exception:
            pass
        finally:
            ap.alive=False
    t = threading.Thread(target=reader, daemon=True)
    t.start()
    ap.reader_thread = t
    return ap

def send_line(ap:AgentProc, line:str):
    if ap.proc.poll() is not None:
        raise RuntimeError(f"Agent '{ap.path}' has exited.")
    ap.proc.stdin.write(line + "\n")
    ap.proc.stdin.flush()

def read_line_with_timeout(ap:AgentProc, timeout_ms:int)->Optional[str]:
    deadline = time.time() + timeout_ms/1000.0
    while time.time() < deadline:
        try:
            line = ap.out_queue.get_nowait()
            if line is None: continue
            if line.strip()=='': continue
            return line
        except queue.Empty:
            time.sleep(0.001)
    return None

def init_board()->List[List[str]]:
    b = [[EMPTY for _ in range(N)] for _ in range(N)]
    b[0][0]=O; b[6][6]=O
    b[0][6]=X; b[6][0]=X
    return b

def inb(r,c)->bool:
    return 0<=r<N and 0<=c<N

def legal_moves(b:List[List[str]], p:str)->List[Move]:
    mv = []
    for r in range(N):
        for c in range(N):
            if b[r][c]!=p: continue
            for dr in range(-2,3):
                for dc in range(-2,3):
                    if dr==0 and dc==0: continue
                    nr, nc = r+dr, c+dc
                    if not inb(nr,nc): continue
                    if b[nr][nc]!=EMPTY: continue
                    d = max(abs(dr),abs(dc))
                    if d==1 or d==2:
                        mv.append(Move(r,c,nr,nc,False))
    if not mv:
        mv.append(Move(-1,-1,-1,-1,True))
    return mv

def flip_gain_if_place(b:List[List[str]], r:int,c:int,p:str)->int:
    flips = 0
    for dr,dc in DIR8:
        nr, nc = r+dr, c+dc
        if inb(nr,nc) and b[nr][nc]!=EMPTY and b[nr][nc]!=p:
            flips += 1
    return flips

def apply_move(b:List[List[str]], mv:Move, p:str):
    if mv.is_pass: return
    d = max(abs(mv.x1-mv.x2), abs(mv.y1-mv.y2))
    if d==1:
        b[mv.x2][mv.y2] = p
    elif d==2:
        b[mv.x2][mv.y2] = p
        b[mv.x1][mv.y1] = EMPTY
    # infection
    for dr,dc in DIR8:
        nr, nc = mv.x2+dr, mv.y2+dc
        if inb(nr,nc) and b[nr][nc]!=EMPTY and b[nr][nc]!=p:
            b[nr][nc] = p

def count_pieces(b)->Tuple[int,int,int]:
    co=cx=ce=0
    for r in range(N):
        for c in range(N):
            if b[r][c]==O: co+=1
            elif b[r][c]==X: cx+=1
            else: ce+=1
    return co,cx,ce

def board_str(b)->str:
    return '\n'.join(''.join(row) for row in b)

def parse_move(line:str)->Optional[Move]:
    parts = line.strip().split()
    if len(parts)!=5 or parts[0]!="MOVE":
        return None
    try:
        x1=int(parts[1]); y1=int(parts[2]); x2=int(parts[3]); y2=int(parts[4])
        if x1==-1 and y1==-1 and x2==-1 and y2==-1:
            return Move(-1,-1,-1,-1,True)
        # convert to 0-based
        return Move(x1-1,y1-1,x2-1,y2-1,False)
    except:
        return None

def is_move_legal(b:List[List[str]], p:str, mv:Move)->bool:
    mvs = legal_moves(b,p)
    if mv.is_pass:
        # pass must be the ONLY legal move
        return len(mvs)==1 and mvs[0].is_pass
    # coordinates check
    if not (inb(mv.x1,mv.y1) and inb(mv.x2,mv.y2)): return False
    if b[mv.x1][mv.y1]!=p: return False
    if b[mv.x2][mv.y2]!=EMPTY: return False
    d = max(abs(mv.x1-mv.x2), abs(mv.y1-mv.y2))
    if d not in (1,2): return False
    # also must be in list of legal moves
    for m in mvs:
        if not m.is_pass and m.x1==mv.x1 and m.y1==mv.y1 and m.x2==mv.x2 and m.y2==mv.y2:
            return True
    return False

def run_single_game(agent1_path:str, agent2_path:str, logf, init_time_ms:int=10000, seed:int=0)->Tuple[int,int,int]:
    random.seed(seed)
    a1 = start_agent(agent1_path)  # FIRST (O)
    a2 = start_agent(agent2_path)  # SECOND (X)

    def safe_kill(ap:AgentProc):
        try:
            if ap.proc.poll() is None:
                ap.proc.kill()
        except Exception:
            pass

    b = init_board()
    my_rem = {O:init_time_ms, X:init_time_ms}
    turns_played = 0
    max_turns = 400

    # READY handshake
    send_line(a1, "READY FIRST")
    send_line(a2, "READY SECOND")

    ok1 = read_line_with_timeout(a1, 3000)
    ok2 = read_line_with_timeout(a2, 3000)
    if ok1!="OK" or ok2!="OK":
        logf.write(f"[ERROR] READY/OK failed: a1='{ok1}' a2='{ok2}'\n")
        safe_kill(a1); safe_kill(a2)
        return (0,0,0)

    current = O
    other = X

    def agent_of(p:str)->AgentProc:
        return a1 if p==O else a2
    def opp_of(p:str)->AgentProc:
        return a2 if p==O else a1

    # Game loop
    while turns_played < max_turns:
        co,cx,ce = count_pieces(b)
        if co==0 or cx==0 or ce==0:
            break
        p = current
        q = other
        ap = agent_of(p)
        op = opp_of(p)

        # Send TURN
        send_line(ap, f"TURN {my_rem[p]} {my_rem[q]}")
        t0 = time.time()
        line = read_line_with_timeout(ap, my_rem[p])
        elapsed_ms = int((time.time()-t0)*1000)

        if line is None:
            logf.write(f"[TLE] Player {p} exceeded time. Elapsed={elapsed_ms}ms Rem={my_rem[p]}ms\n")
            break

        # Parse move
        mv = parse_move(line)
        if mv is None or not is_move_legal(b, p, mv):
            logf.write(f"[RE] Player {p} invalid move line='{line}'\n")
            break

        # Apply move
        apply_move(b, mv, p)

        # Notify opponent with OPP (coords in 1-based; PASS => -1)
        if mv.is_pass:
            send_line(op, f"OPP -1 -1 -1 -1 {elapsed_ms}")
        else:
            send_line(op, f"OPP {mv.x1+1} {mv.y1+1} {mv.x2+1} {mv.y2+1} {elapsed_ms}")

        # Update clocks
        my_rem[p] = max(0, my_rem[p] - elapsed_ms)

        # Log
        logf.write(f"[TURN {turns_played+1}] Player {p} line='{line}' time={elapsed_ms}ms rem={my_rem[p]}ms\n")
        logf.write(board_str(b) + "\n\n")
        turns_played += 1

        # swap
        current, other = other, current

    # End: send FINISH to both
    try:
        send_line(a1, "FINISH")
    except Exception: pass
    try:
        send_line(a2, "FINISH")
    except Exception: pass

    # Read outputs (optional small drain)
    time.sleep(0.05)
    safe_kill(a1); safe_kill(a2)

    co,cx,ce = count_pieces(b)
    diff = co - cx  # O - X
    logf.write(f"[END] O={co} X={cx} empty={ce} diff(O-X)={diff} turns={turns_played}\n")
    return co,cx,diff


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--agent1', default='./agent_v1', help='FIRST (O) executable path')
    parser.add_argument('--agent2', default='./sample', help='SECOND (X) executable path')
    parser.add_argument('--log', default='auto')
    parser.add_argument('--time', type=int, default=10000, help='Initial time per side in ms')
    parser.add_argument('--seed', type=int, default=0)
    parser.add_argument('--swap', action='store_true', help='Run two games swapping roles and summarize')
    args = parser.parse_args()

    # --- Auto log path ---
    def agent_name(pth:str)->str:
        base = os.path.basename(pth.rstrip("/\\"))
        name, ext = os.path.splitext(base)
        return name or base or "agent"

    if not args.log or args.log.lower() == "auto":
        a1n = agent_name(args.agent1)
        a2n = agent_name(args.agent2)
        log_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), "game_log")
        os.makedirs(log_dir, exist_ok=True)
        auto_log = f"{a1n}_vs_{a2n}.txt"
        args.log = os.path.join(log_dir, auto_log)

    if args.swap:
        # Game 1: agent1 as O
        with open(args.log, 'w', encoding='utf-8') as f:
            f.write("=== Game 1: agent1=O, agent2=X ===\n")
            co,cx,diff1 = run_single_game(args.agent1, args.agent2, f, args.time, seed=args.seed)
            f.write(f"Result Game1: O={co} X={cx} diff(O-X)={diff1}\n")
            # Human-readable verdict
            if diff1 > 0:
                f.write(f"Verdict Game1: agent1 (O) wins by {diff1}\n\n")
            elif diff1 < 0:
                f.write(f"Verdict Game1: agent2 (X) wins by {-diff1}\n\n")
            else:
                f.write("Verdict Game1: Draw\n\n")

            # Game 2: swapped roles
            f.write("=== Game 2: agent1=X, agent2=O ===\n")
            co2,cx2,diff2 = run_single_game(args.agent2, args.agent1, f, args.time, seed=args.seed+1)
            f.write(f"Result Game2: O={co2} X={cx2} diff(O-X)={diff2}\n")
            # For Game2, O is agent2 and X is agent1
            if diff2 > 0:
                f.write(f"Verdict Game2: agent2 (O) wins by {diff2}\n\n")
            elif diff2 < 0:
                f.write(f"Verdict Game2: agent1 (X) wins by {-diff2}\n\n")
            else:
                f.write("Verdict Game2: Draw\n\n")

            # From agent1 perspective: agent1 was O in G1, X in G2 → total diff = diff1 - diff2
            total = diff1 - diff2
            f.write("=== Summary (agent1 perspective) ===\n")
            f.write(f"Total diff = (G1 O-X) - (G2 O-X) = {diff1} - {diff2} = {total}\n")
            if total > 0:
                f.write(f"Overall: agent1 beats agent2 by {total}\n")
            elif total < 0:
                f.write(f"Overall: agent2 beats agent1 by {-total}\n")
            else:
                f.write("Overall: Draw\n")
        print(f"Swap mode complete. Log: {args.log}")
    else:
        with open(args.log, 'w', encoding='utf-8') as f:
            co,cx,diff = run_single_game(args.agent1, args.agent2, f, args.time, seed=args.seed)
            # For single game, agent1 is O, agent2 is X
            verdict = "Draw"
            margin = abs(diff)
            if diff > 0: verdict = f"agent1 (O) wins by {margin}"
            elif diff < 0: verdict = f"agent2 (X) wins by {margin}"
            print(f"Game finished. O={co} X={cx} diff(O-X)={diff}. {verdict}. Log: {args.log}")
if __name__=='__main__':
    main()
