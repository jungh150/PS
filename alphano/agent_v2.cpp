// Ataxx-like 7x7 agent (V2.1): Alpha-Beta + TT + Iterative Deepening + Correct Move Ordering + Robust Time Checks
// Build: g++ -O2 -std=gnu++17 -s -o agent_v2 agent_v2.cpp
#include <bits/stdc++.h>
using namespace std;

static const int N = 7;
enum Cell : char { EMPTY='.', O='O', X='X' };

struct Move { int x1,y1,x2,y2; bool isPass; };

struct ZobEntry {
    uint64_t key=0;
    int depth=-1;
    int value=0;           // score from 'me' perspective
    char flag=0;           // 0=exact, 1=alpha, 2=beta
    Move best{ -1,-1,-1,-1,true };
};

struct Agent {
    array<array<char,N>,N> b{};
    char me = O, opp = X;
    bool initialized=false;

    // Timing
    chrono::steady_clock::time_point deadline;
    bool time_up=false;

    // Zobrist
    uint64_t Z[2][N][N]{}; // [0]=O, [1]=X
    uint64_t Z_side{};
    unordered_map<uint64_t, ZobEntry> TT;

    Agent(){ reset(); init_zob(); }

    void reset(){
        for(int i=0;i<N;i++) for(int j=0;j<N;j++) b[i][j]=EMPTY;
        b[0][0]=O; b[6][6]=O;
        b[0][6]=X; b[6][0]=X;
        initialized=true;
        TT.clear();
        TT.reserve(1<<18);
    }

    void init_zob(){
        std::mt19937_64 rng(0x244cafeefaceULL);
        for(int p=0;p<2;p++)
            for(int r=0;r<N;r++) for(int c=0;c<N;c++) Z[p][r][c]=rng();
        Z_side = rng();
    }

    inline bool inb(int r,int c) const { return 0<=r && r<N && 0<=c && c<N; }
    inline char other(char p) const { return p==O?X:O; }

    // Hash
    uint64_t hash_board(const array<array<char,N>,N>& a, char side) const {
        uint64_t h=0;
        for(int r=0;r<N;r++) for(int c=0;c<N;c++){
            if(a[r][c]==O) h^=Z[0][r][c];
            else if(a[r][c]==X) h^=Z[1][r][c];
        }
        if(side==X) h^=Z_side;
        return h;
    }

    // Apply a move
    void apply_move(array<array<char,N>,N>& a, const Move& mv, char p) const {
        if(mv.isPass) return;
        int d = max(abs(mv.x1-mv.x2), abs(mv.y1-mv.y2));
        if(d==1){
            a[mv.x2][mv.y2] = p;
        }else if(d==2){
            a[mv.x2][mv.y2] = p;
            a[mv.x1][mv.y1] = EMPTY;
        }
        for(int dr=-1; dr<=1; ++dr){
            for(int dc=-1; dc<=1; ++dc){
                if(dr==0 && dc==0) continue;
                int nr=mv.x2+dr, nc=mv.y2+dc;
                if(inb(nr,nc) && a[nr][nc]!=EMPTY && a[nr][nc]!=p) a[nr][nc]=p;
            }
        }
    }

    vector<Move> legal_moves(const array<array<char,N>,N>& a, char p) const {
        vector<Move> mv;
        for(int r=0;r<N;r++){
            for(int c=0;c<N;c++){
                if(a[r][c]!=p) continue;
                for(int dr=-2; dr<=2; ++dr){
                    for(int dc=-2; dc<=2; ++dc){
                        if(dr==0 && dc==0) continue;
                        int nr=r+dr, nc=c+dc;
                        if(!inb(nr,nc)) continue;
                        if(a[nr][nc]!=EMPTY) continue;
                        int d=max(abs(dr),abs(dc));
                        if(d==1 || d==2) mv.push_back({r,c,nr,nc,false});
                    }
                }
            }
        }
        if(mv.empty()) mv.push_back({-1,-1,-1,-1,true});
        return mv;
    }

    int mobility(const array<array<char,N>,N>& a, char p) const {
        auto mv=legal_moves(a,p);
        return (mv.size()==1 && mv[0].isPass)?0:(int)mv.size();
    }

    int frontier_count(const array<array<char,N>,N>& a, char p) const {
        char q = (p==O?X:O);
        int cnt=0;
        for(int r=0;r<N;r++) for(int c=0;c<N;c++){
            if(a[r][c]!=p) continue;
            bool adj=false;
            for(int dr=-1; dr<=1; ++dr){
                for(int dc=-1; dc<=1; ++dc){
                    if(dr==0 && dc==0) continue;
                    int nr=r+dr, nc=c+dc;
                    if(inb(nr,nc) && a[nr][nc]==q){ adj=true; break; }
                }
                if(adj) break;
            }
            if(adj) cnt++;
        }
        return cnt;
    }

    pair<int,int> counts(const array<array<char,N>,N>& a) const {
        int co=0,cx=0;
        for(int r=0;r<N;r++) for(int c=0;c<N;c++){
            if(a[r][c]==O) co++; else if(a[r][c]==X) cx++;
        }
        return {co,cx};
    }

    int center_bonus_cell(int r,int c) const {
        int dist = max(abs(r-3), abs(c-3));
        return 3 - dist;
    }
    int stability_bonus_cell(int r,int c) const {
        bool corner = ((r==0||r==6) && (c==0||c==6));
        if(corner) return 2;
        bool edge = (r==0||r==6||c==0||c==6);
        return edge?1:0;
    }

    int region_parity_bonus(const array<array<char,N>,N>& a) const {
        vector<vector<int>> vis(N, vector<int>(N,0));
        int odd=0, even=0;
        const int drs[8]={-1,-1,-1,0,0,1,1,1};
        const int dcs[8]={-1,0,1,-1,1,-1,0,1};
        for(int r=0;r<N;r++) for(int c=0;c<N;c++){
            if(a[r][c]!=EMPTY || vis[r][c]) continue;
            int sz=0;
            queue<pair<int,int>> q;
            q.push({r,c}); vis[r][c]=1;
            while(!q.empty()){
                auto [cr,cc]=q.front(); q.pop();
                sz++;
                for(int k=0;k<8;k++){
                    int nr=cr+drs[k], nc=cc+dcs[k];
                    if(inb(nr,nc) && !vis[nr][nc] && a[nr][nc]==EMPTY){
                        vis[nr][nc]=1; q.push({nr,nc});
                    }
                }
            }
            if(sz%2==1) odd++; else even++;
        }
        return odd - even;
    }

    int flip_gain_if_place(const array<array<char,N>,N>& a, int r,int c, char p) const {
        int flips=0;
        for(int dr=-1; dr<=1; ++dr) for(int dc=-1; dc<=1; ++dc){
            if(dr==0 && dc==0) continue;
            int nr=r+dr, nc=c+dc;
            if(inb(nr,nc) && a[nr][nc]!=EMPTY && a[nr][nc]!=p) flips++;
        }
        return flips;
    }

    // Heuristic quick eval of a move on arbitrary board 'a' for side 'p'
    double heuristic_move_score_board(const array<array<char,N>,N>& a, char p, const Move& mv) const {
        if(mv.isPass) return -1e9;
        int my_frontier_before = frontier_count(a, p);
        int my_mob_before = mobility(a, p);
        int opp_mob_before = mobility(a, other(p));

        auto after = a;
        int fg = flip_gain_if_place(a, mv.x2, mv.y2, p);
        apply_move(after, mv, p);

        int my_frontier_after = frontier_count(after, p);
        int my_mob_after = mobility(after, p);
        int opp_mob_after = mobility(after, other(p));

        int d_frontier = my_frontier_after - my_frontier_before;
        int d_mobility = (my_mob_after - my_mob_before) - (opp_mob_after - opp_mob_before);
        int center_b = center_bonus_cell(mv.x2, mv.y2);
        int stab_b = stability_bonus_cell(mv.x2, mv.y2);

        int empties=0; for(int r=0;r<N;r++) for(int c=0;c<N;c++) if(after[r][c]==EMPTY) empties++;
        int region_b = (empties<=10)? region_parity_bonus(after): 0;

        const double W_flip_gain   = 5.0;
        const double W_d_mobility  = 7.0;
        const double W_d_frontier  = -4.0;
        const double W_center      = 2.0;
        const double W_stability   = 3.0;
        const double W_region      = 6.0;

        double score=0;
        score += W_flip_gain*fg;
        score += W_d_mobility*d_mobility;
        score += W_d_frontier*d_frontier;
        score += W_center*center_b;
        score += W_stability*stab_b;
        score += W_region*region_b;

        int d = max(abs(mv.x1-mv.x2), abs(mv.y1-mv.y2));
        score += (d==1?0.05:0.0); // prefer division lightly

        int adj_friend=0;
        for(int dr=-1; dr<=1; ++dr) for(int dc=-1; dc<=1; ++dc){
            if(dr==0 && dc==0) continue;
            int nr=mv.x2+dr, nc=mv.y2+dc;
            if(inb(nr,nc) && a[nr][nc]==p) adj_friend++;
        }
        score += 0.03 * adj_friend;
        return score;
    }

    // Static evaluation of board 'a' from perspective 'me'
    int evaluate_board(const array<array<char,N>,N>& a) const {
        auto [co,cx] = counts(a);
        int my_cnt = (me==O?co:cx);
        int op_cnt = (me==O?cx:co);
        int piece_diff = my_cnt - op_cnt;

        int mob_my = mobility(a, me);
        int mob_op = mobility(a, opp);
        int mobility_diff = mob_my - mob_op;

        int frontier_my = frontier_count(a, me);
        int frontier_op = frontier_count(a, opp);
        int frontier_term = -(frontier_my - frontier_op);

        int center=0, stab=0;
        for(int r=0;r<N;r++) for(int c=0;c<N;c++){
            if(a[r][c]==me){ center += center_bonus_cell(r,c); stab += stability_bonus_cell(r,c); }
            else if(a[r][c]==opp){ center -= center_bonus_cell(r,c); stab -= stability_bonus_cell(r,c); }
        }

        int empties=0; for(int r=0;r<N;r++) for(int c=0;c<N;c++) if(a[r][c]==EMPTY) empties++;
        int region_b = (empties<=10)? region_parity_bonus(a): 0;

        // Phase weighting
        double phase = 1.0 - (empties/49.0);
        double W_piece = 8.0*phase + 2.0;
        double W_mob   = 10.0*(1.0-phase) + 2.0;
        double W_front = 4.0;
        double W_cent  = 1.5;
        double W_stab  = 2.5;
        double W_reg   = 7.0*phase;

        double val = 0.0;
        val += W_piece * piece_diff;
        val += W_mob   * mobility_diff;
        val += W_front * frontier_term;
        val += W_cent  * center;
        val += W_stab  * stab;
        val += W_reg   * region_b;

        return (int)llround(val);
    }

    inline bool time_exceeded() {
        if (chrono::steady_clock::now() >= deadline) { time_up = true; return true; }
        return false;
    }

    bool is_terminal(const array<array<char,N>,N>& a) const {
        auto [co,cx] = counts(a);
        if(co==0 || cx==0) return true;
        int empties=0; for(int r=0;r<N;r++) for(int c=0;c<N;c++) if(a[r][c]==EMPTY) empties++;
        if(empties==0) return true;
        return false;
    }

    // Move ordering on board 'a' for side 'p'
    vector<Move> order_moves(const array<array<char,N>,N>& a, char p) const {
        vector<Move> mv = legal_moves(a, p);
        if(mv.size()==1) return mv;
        struct Cand{ Move mv; double key; int dist; int center; };
        vector<Cand> cand; cand.reserve(mv.size());
        for(const auto &m: mv){
            if(m.isPass){ cand.push_back({m,-1e9,0,0}); continue; }
            int d = max(abs(m.x1-m.x2), abs(m.y1-m.y2));
            int center = -max(abs(m.x2-3), abs(m.y2-3)); // nearer center -> larger
            double s = heuristic_move_score_board(a, p, m);
            cand.push_back({m, s, d, center});
        }
        stable_sort(cand.begin(), cand.end(), [](const Cand& A, const Cand& B){
            if (A.key!=B.key) return A.key > B.key;
            if (A.dist!=B.dist) return A.dist < B.dist; // prefer division
            if (A.center!=B.center) return A.center > B.center;
            return false;
        });
        vector<Move> out; out.reserve(cand.size());
        for(auto &c: cand) out.push_back(c.mv);
        return out;
    }

    // Alpha-beta with TT and time control
    int alphabeta(const array<array<char,N>,N>& a, int depth, int alpha, int beta, char side, bool& anyMove, Move* bestOut){
        if(time_up || time_exceeded()) return evaluate_board(a);
        if(depth==0 || is_terminal(a)){
            return evaluate_board(a);
        }

        uint64_t key = hash_board(a, side);
        auto it = TT.find(key);
        if(it!=TT.end() && it->second.depth>=depth){
            auto &e = it->second;
            if(e.flag==0) { if(bestOut) *bestOut = e.best; return e.value; }
            else if(e.flag==1 && e.value<=alpha) { if(bestOut) *bestOut = e.best; return alpha; }
            else if(e.flag==2 && e.value>=beta)  { if(bestOut) *bestOut = e.best; return beta; }
        }

        vector<Move> moves = order_moves(a, side);
        anyMove = !(moves.size()==1 && moves[0].isPass);

        int bestVal = (side==me? INT_MIN/2 : INT_MAX/2);
        Move bestMv = { -1,-1,-1,-1,true };

        int alpha0 = alpha, beta0 = beta; // keep originals for TT flagging

        for(size_t i=0;i<moves.size();++i){
            if(time_exceeded()) break;
            const Move &m = moves[i];
            array<array<char,N>,N> nxt = a;
            if(!m.isPass) apply_move(nxt, m, side);
            char nxtSide = other(side);

            bool oppAny=false;
            int val = alphabeta(nxt, depth-1, alpha, beta, nxtSide, oppAny, nullptr);
            if(time_up) return evaluate_board(a);

            if(side==me){
                if(val>bestVal){ bestVal=val; bestMv=m; }
                alpha = max(alpha, bestVal);
                if(alpha>=beta) break;
            }else{
                if(val<bestVal){ bestVal=val; bestMv=m; }
                beta = min(beta, bestVal);
                if(alpha>=beta) break;
            }
        }

        ZobEntry e; e.key=key; e.depth=depth; e.value=bestVal; e.best=bestMv;
        if(bestVal<=alpha0) e.flag=1;       // fail-low
        else if(bestVal>=beta0) e.flag=2;   // fail-high
        else e.flag=0;                      // exact
        TT[key]=e;

        if(bestOut) *bestOut = bestMv;
        return bestVal;
    }

    Move search_iterative(int maxDepth, long long budget_ms){
        time_up=false;
        deadline = chrono::steady_clock::now() + chrono::milliseconds(budget_ms);
        Move best = { -1,-1,-1,-1,true };

        for(int d=1; d<=maxDepth; ++d){
            if(time_exceeded()) break;
            bool anyMove=false;
            Move cand;
            int val = alphabeta(b, d, INT_MIN/4, INT_MAX/4, me, anyMove, &cand);
            if(time_up) break;
            if(anyMove && !cand.isPass){
                best = cand;
            }else if(!anyMove){
                best = { -1,-1,-1,-1,true };
                break;
            }
        }
        if(best.isPass){
            auto mv = legal_moves(b, me);
            if(!(mv.size()==1 && mv[0].isPass)){
                vector<pair<double,Move>> cands;
                for(auto &m: mv) cands.push_back({heuristic_move_score_board(b, me, m), m});
                sort(cands.begin(), cands.end(), [](auto &A, auto &B){ return A.first>B.first; });
                best = cands.front().second;
            }
        }
        return best;
    }

    void handle_ready(const string& who){
        if(who=="FIRST"){ me=O; opp=X; }
        else { me=X; opp=O; }
        cout << "OK" << endl;
        cout.flush();
    }

    void apply_opp_line(int x1,int y1,int x2,int y2){
        if(x1==-1 && y1==-1 && x2==-1 && y2==-1) return;
        Move mv{ x1-1, y1-1, x2-1, y2-1, false };
        apply_move(b, mv, opp);
    }

    Move choose_move_with_time(long long my_time, long long /*opp_time*/){
        // Budget policy: 8%의 남은 시간 + 120ms, 최대 1200ms. 세이프티 마진 10ms.
        long long budget = (long long)min( 1200.0, max( 150.0, my_time*0.08 + 120.0 ) );
        budget = min(budget, max(0LL, my_time - 10));
        if(budget<=0){
            auto mv = legal_moves(b, me);
            if(mv.size()==1) return mv[0];
            double best=-1e300; Move bestm={-1,-1,-1,-1,true};
            for(auto &m: mv){ double s=heuristic_move_score_board(b, me, m); if(s>best){best=s; bestm=m;} }
            return bestm;
        }
        int maxDepth = 5;
        return search_iterative(maxDepth, budget);
    }

    void play_turn(long long my_time, long long opp_time){
        Move mv = choose_move_with_time(my_time, opp_time);
        if(mv.isPass){
            cout << "MOVE -1 -1 -1 -1" << endl;
            cout.flush();
            return;
        }
        cout << "MOVE " << (mv.x1+1) << ' ' << (mv.y1+1) << ' ' << (mv.x2+1) << ' ' << (mv.y2+1) << endl;
        cout.flush();
        apply_move(b, mv, me);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Agent agent;
    string cmd;
    while(true){
        if(!(cin>>cmd)) break;
        if(cmd=="READY"){
            string role; cin>>role;
            agent.reset();
            agent.handle_ready(role);
        } else if(cmd=="TURN"){
            long long myt, oppt; cin>>myt>>oppt;
            agent.play_turn(myt, oppt);
        } else if(cmd=="OPP"){
            int x1,y1,x2,y2; long long t; cin>>x1>>y1>>x2>>y2>>t;
            agent.apply_opp_line(x1,y1,x2,y2);
        } else if(cmd=="FINISH"){
            break;
        } else {
            string rest; getline(cin, rest);
        }
    }
    return 0;
}
