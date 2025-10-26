// agent_v4_2.cpp
// Build: g++ -O2 -std=gnu++17 -s -o agent_v4_2 agent_v4_2.cpp
#include <bits/stdc++.h>
using namespace std;

static const int N=7;
enum Cell: char { EMPTY='.', O='O', X='X' };
struct Move{ int x1,y1,x2,y2; bool isPass; };

struct ZobEntry{
    uint64_t key=0;
    int depth=-1;
    int value=0;
    unsigned char flag=0; // 0=exact,1=alpha,2=beta
    Move best{-1,-1,-1,-1,true};
};

struct Agent{
    array<array<char,N>,N> b{};
    char me=O, opp=X;

    chrono::steady_clock::time_point deadline;
    bool time_up=false;

    uint64_t Z[2][N][N]{};
    uint64_t Z_side{};
    unordered_map<uint64_t,ZobEntry> TT;

    static const int MAXD=18;
    int History[2][N][N]{};
    Move Killer[MAXD][2];

    Agent(){ reset(); init_zob(); }

    void reset(){
        for(int r=0;r<N;r++) for(int c=0;c<N;c++) b[r][c]=EMPTY;
        b[0][0]=O; b[6][6]=O; b[0][6]=X; b[6][0]=X;
        TT.clear(); TT.reserve(1<<18);
        memset(History,0,sizeof(History));
        for(int d=0; d<MAXD; ++d){ Killer[d][0]={-1,-1,-1,-1,true}; Killer[d][1]=Killer[d][0]; }
    }
    void init_zob(){
        mt19937_64 rng(0x9e3779b97f4a7c15ULL);
        for(int p=0;p<2;p++)
            for(int r=0;r<N;r++) for(int c=0;c<N;c++) Z[p][r][c]=rng();
        Z_side=rng();
    }
    inline bool inb(int r,int c) const { return 0<=r&&r<N&&0<=c&&c<N; }
    inline char other(char p) const { return p==O?X:O; }
    inline int sideIndex(char p) const { return p==O?0:1; }

    uint64_t hash_board(const array<array<char,N>,N>& a, char side) const{
        uint64_t h=0;
        for(int r=0;r<N;r++) for(int c=0;c<N;c++){
            if(a[r][c]==O) h^=Z[0][r][c];
            else if(a[r][c]==X) h^=Z[1][r][c];
        }
        if(side==X) h^=Z_side;
        return h;
    }

    void apply_move(array<array<char,N>,N>& a, const Move& mv, char p) const{
        if(mv.isPass) return;
        int d=max(abs(mv.x1-mv.x2),abs(mv.y1-mv.y2));
        if(d==1){
            a[mv.x2][mv.y2]=p;
        }else{
            a[mv.x2][mv.y2]=p; a[mv.x1][mv.y1]=EMPTY;
        }
        for(int dr=-1; dr<=1; ++dr) for(int dc=-1; dc<=1; ++dc){
            if(dr==0&&dc==0) continue;
            int nr=mv.x2+dr, nc=mv.y2+dc;
            if(inb(nr,nc) && a[nr][nc]!=EMPTY && a[nr][nc]!=p) a[nr][nc]=p;
        }
    }

    vector<Move> legal_moves(const array<array<char,N>,N>& a, char p) const{
        vector<Move> mv;
        for(int r=0;r<N;r++) for(int c=0;c<N;c++){
            if(a[r][c]!=p) continue;
            for(int dr=-2; dr<=2; ++dr) for(int dc=-2; dc<=2; ++dc){
                if(dr==0&&dc==0) continue;
                int nr=r+dr, nc=c+dc;
                if(!inb(nr,nc) || a[nr][nc]!=EMPTY) continue;
                int d=max(abs(dr),abs(dc));
                if(d==1||d==2) mv.push_back({r,c,nr,nc,false});
            }
        }
        if(mv.empty()) mv.push_back({-1,-1,-1,-1,true});
        return mv;
    }

    pair<int,int> counts(const array<array<char,N>,N>& a) const{
        int co=0,cx=0;
        for(int r=0;r<N;r++) for(int c=0;c<N;c++){
            if(a[r][c]==O) co++; else if(a[r][c]==X) cx++;
        }
        return {co,cx};
    }

    int mobility(const array<array<char,N>,N>& a, char p) const{
        auto mv=legal_moves(a,p);
        return (mv.size()==1 && mv[0].isPass)?0:(int)mv.size();
    }

    int frontier_count(const array<array<char,N>,N>& a, char p) const{
        char q=other(p);
        int cnt=0;
        for(int r=0;r<N;r++) for(int c=0;c<N;c++){
            if(a[r][c]!=p) continue;
            bool adj=false;
            for(int dr=-1; dr<=1; ++dr){ for(int dc=-1; dc<=1; ++dc){
                if(dr==0&&dc==0) continue;
                int nr=r+dr, nc=c+dc;
                if(inb(nr,nc) && a[nr][nc]==q){ adj=true; break; }
            } if(adj) break; }
            if(adj) cnt++;
        }
        return cnt;
    }

    int center_bonus_cell(int r,int c) const{
        int dist=max(abs(r-3),abs(c-3));
        return 3-dist; // center 3..0
    }
    int stability_bonus_cell(int r,int c) const{
        bool corner=((r==0||r==6)&&(c==0||c==6));
        if(corner) return 2;
        bool edge=(r==0||r==6||c==0||c==6);
        return edge?1:0;
    }

    int region_parity_bonus(const array<array<char,N>,N>& a) const{
        vector<vector<int>> vis(N, vector<int>(N,0));
        const int drs[8]={-1,-1,-1,0,0,1,1,1};
        const int dcs[8]={-1,0,1,-1,1,-1,0,1};
        int odd=0, even=0;
        for(int r=0;r<N;r++) for(int c=0;c<N;c++){
            if(a[r][c]!=EMPTY || vis[r][c]) continue;
            int sz=0;
            queue<pair<int,int>> q; q.push({r,c}); vis[r][c]=1;
            while(!q.empty()){
                auto [cr,cc]=q.front(); q.pop(); sz++;
                for(int k=0;k<8;k++){
                    int nr=cr+drs[k], nc=cc+dcs[k];
                    if(inb(nr,nc)&&!vis[nr][nc]&&a[nr][nc]==EMPTY){ vis[nr][nc]=1; q.push({nr,nc}); }
                }
            }
            if(sz&1) odd++; else even++;
        }
        return odd-even;
    }

    inline bool time_exceeded(){
        if(chrono::steady_clock::now()>=deadline){ time_up=true; return true; }
        return false;
    }

    bool is_terminal(const array<array<char,N>,N>& a) const{
        auto [co,cx]=counts(a);
        if(co==0 || cx==0) return true;
        int emp=0; for(int r=0;r<N;r++) for(int c=0;c<N;c++) if(a[r][c]==EMPTY) emp++;
        return emp==0;
    }

    int flip_gain_if_place(const array<array<char,N>,N>& a, int r,int c, char p) const{
        int flips=0;
        for(int dr=-1; dr<=1; ++dr) for(int dc=-1; dc<=1; ++dc){
            if(dr==0&&dc==0) continue;
            int nr=r+dr, nc=c+dc;
            if(inb(nr,nc) && a[nr][nc]!=EMPTY && a[nr][nc]!=p) flips++;
        }
        return flips;
    }

    int evaluate_board(const array<array<char,N>,N>& a) const{
        auto [co,cx]=counts(a);
        int my=(me==O?co:cx), op=(me==O?cx:co);
        int piece = my-op;

        int mob = mobility(a,me) - mobility(a,opp);
        int frontier = -(frontier_count(a,me) - frontier_count(a,opp));

        int center=0, stab=0;
        for(int r=0;r<N;r++) for(int c=0;c<N;c++){
            if(a[r][c]==me){ center+=center_bonus_cell(r,c); stab+=stability_bonus_cell(r,c); }
            else if(a[r][c]==opp){ center-=center_bonus_cell(r,c); stab-=stability_bonus_cell(r,c); }
        }
        int emp=0; for(int r=0;r<N;r++) for(int c=0;c<N;c++) if(a[r][c]==EMPTY) emp++;
        int reg = (emp<=12 ? region_parity_bonus(a) : 0);

        // 초반 중앙/프론티어 비중 강화
        double phase = 1.0 - (emp/49.0);
        double W_piece = 9.0*phase + 1.6;
        double W_mob   = 9.0*(1.0-phase) + 3.0;
        double W_front = 5.0;      // ↑
        double W_cent  = 2.2;      // ↑
        double W_stab  = 3.0;
        double W_reg   = 8.0*phase;

        double val=0;
        val += W_piece*piece;
        val += W_mob*mob;
        val += W_front*frontier;
        val += W_cent*center;
        val += W_stab*stab;
        val += W_reg*reg;

        return (int)llround(val);
    }

    // early diagonal discipline
    inline bool on_main_diag(int r,int c) const { return r==c; }
    inline int center_dist(int r,int c) const { return max(abs(r-3),abs(c-3)); }

    double heuristic_move_score_board(const array<array<char,N>,N>& a, char p, const Move& mv) const{
        if(mv.isPass) return -1e9;

        int d=max(abs(mv.x1-mv.x2),abs(mv.y1-mv.y2));
        int fg=flip_gain_if_place(a,mv.x2,mv.y2,p);

        int emp=0; for(int r=0;r<N;r++) for(int c=0;c<N;c++) if(a[r][c]==EMPTY) emp++;
        bool early = (emp>=40);

        // 초반: 무의미 도약 억제
        if(early && d==2 && fg<=1) return -1e8;

        // 대각선 규율: 대각 위에서 옆으로 이탈/중심거리 증가 금지(강페널티)
        if(early && on_main_diag(mv.x1,mv.y1)){
            int before=center_dist(mv.x1,mv.y1);
            int after =center_dist(mv.x2,mv.y2);
            bool diagProgress = (mv.x2-mv.x1)==(mv.y2-mv.y1); // 대각 진행
            if(after>before && fg<=2) return -9e7;           // 중심 멀어짐
            if(!diagProgress && fg<=2) return -7e7;          // 옆으로 이탈
        }

        auto after=a; apply_move(after,mv,p);

        int my_front_before=frontier_count(a,p);
        int my_front_after =frontier_count(after,p);
        int d_front = my_front_after - my_front_before;

        int my_mob_before=mobility(a,p);
        int my_mob_after =mobility(after,p);
        int op_mob_after =mobility(after,other(p));
        int d_mob = (my_mob_after - my_mob_before) - (op_mob_after - mobility(a,other(p)));

        int center = center_bonus_cell(mv.x2,mv.y2);
        int stab   = stability_bonus_cell(mv.x2,mv.y2);

        // one-ply opponent best reply penalty
        double opp_best=0.0;
        {
            auto opMoves = legal_moves(after, other(p));
            for(const auto &om: opMoves){
                if(om.isPass) continue;
                int ofg = flip_gain_if_place(after, om.x2, om.y2, other(p));
                int oc  = center_bonus_cell(om.x2, om.y2);
                int od  = max(abs(om.x1-om.x2), abs(om.y1-om.y2));
                double s = 6.5*ofg + 2.5*oc + (od==1?0.05:0.0);
                if(s>opp_best) opp_best=s;
            }
        }

        const double W_flip=5.0, W_dm=7.5, W_df=-4.5, W_cent=2.4, W_stab=3.0;
        double sc=0;
        sc += W_flip*fg;
        sc += W_dm*d_mob;
        sc += W_df*d_front;
        sc += W_cent*center;
        sc += W_stab*stab;
        sc += (d==1?0.08:0.0);

        // 초반: 중심 접근/대각 진행 보너스
        if(early){
            int before=center_dist(mv.x1,mv.y1);
            int after =center_dist(mv.x2,mv.y2);
            sc += 0.8*(before-after); // 중심 가까워질수록 +
            if(on_main_diag(mv.x1,mv.y1) && (mv.x2-mv.x1)==(mv.y2-mv.y1)) sc += 0.6;
        }

        return sc - 0.55*opp_best;
    }

    struct Cand{ Move m; double key; bool tt; bool killer; int hist; int dist; int center; };

    vector<Move> order_moves(const array<array<char,N>,N>& a, char side, int depth){
        vector<Move> mv = legal_moves(a, side);
        if(mv.size()<=1) return mv;

        Move ttbest={-1,-1,-1,-1,true};
        auto it=TT.find(hash_board(a,side));
        if(it!=TT.end() && !it->second.best.isPass) ttbest=it->second.best;

        vector<Cand> cs; cs.reserve(mv.size());
        for(const auto &m: mv){
            bool isTT = (!ttbest.isPass && m.x1==ttbest.x1 && m.y1==ttbest.y1 && m.x2==ttbest.x2 && m.y2==ttbest.y2);
            bool isK = false;
            if(depth<MAXD){
                for(int i=0;i<2;i++){
                    const Move &km=Killer[depth][i];
                    if(!km.isPass && m.x1==km.x1 && m.y1==km.y1 && m.x2==km.x2 && m.y2==km.y2) { isK=true; break; }
                }
            }
            int hist = History[sideIndex(side)][m.x2][m.y2];
            int d=max(abs(m.x1-m.x2),abs(m.y1-m.y2));
            int center = -max(abs(m.x2-3),abs(m.y2-3));
            double h = heuristic_move_score_board(a,side,m);
            cs.push_back({m,h,isTT,isK,hist,d,center});
        }

        stable_sort(cs.begin(), cs.end(), [](const Cand& A, const Cand& B){
            if(A.tt!=B.tt) return A.tt>B.tt;
            if(A.killer!=B.killer) return A.killer>B.killer;
            if(A.hist!=B.hist) return A.hist>B.hist;
            if(A.key!=B.key) return A.key>B.key;
            if(A.dist!=B.dist) return A.dist<B.dist;
            if(A.center!=B.center) return A.center>B.center;
            return false;
        });

        vector<Move> out; out.reserve(cs.size());
        for(auto &c: cs) out.push_back(c.m);
        return out;
    }

    bool tactical_explosive(const array<array<char,N>,N>& a, const Move& m, char side) const{
        if(m.isPass) return false;
        int d=max(abs(m.x1-m.x2),abs(m.y1-m.y2));
        int fg = flip_gain_if_place(a,m.x2,m.y2,side);
        int beforeF = frontier_count(a,side);
        auto after=a; apply_move(after,m,side);
        int afterF = frontier_count(after,side);
        int adj_enemy=0;
        for(int dr=-1; dr<=1; ++dr) for(int dc=-1; dc<=1; ++dc){
            if(dr==0&&dc==0) continue;
            int nr=m.x2+dr, nc=m.y2+dc;
            if(inb(nr,nc) && a[nr][nc]==other(side)) adj_enemy++;
        }
        return (fg>=4) || (afterF-beforeF>=3) || (d==2 && adj_enemy>=3);
    }

    inline int futility_margin(int depth) const{
        return (depth<=2)? 120 : 0; // 살짝 완화(너무 과감한 커트 방지)
    }

    int alphabeta(array<array<char,N>,N>& a, int depth, int alpha, int beta, char side, int ply, Move* bestOut){
        if(time_up || time_exceeded()) return evaluate_board(a);
        if(depth<=0 || is_terminal(a)) return evaluate_board(a);

        uint64_t key = hash_board(a, side);
        auto it=TT.find(key);
        if(it!=TT.end() && it->second.depth>=depth){
            auto &e=it->second;
            if(e.flag==0){ if(bestOut) *bestOut=e.best; return e.value; }
            else if(e.flag==1 && e.value<=alpha){ if(bestOut) *bestOut=e.best; return alpha; }
            else if(e.flag==2 && e.value>=beta){ if(bestOut) *bestOut=e.best; return beta; }
        }

        vector<Move> moves = order_moves(a, side, ply);
        if(moves.size()==1 && moves[0].isPass){
            return evaluate_board(a);
        }

        int alpha0=alpha, beta0=beta;
        int bestVal = (side==me? INT_MIN/2 : INT_MAX/2);
        Move bestMv = { -1,-1,-1,-1,true };
        int statEval = evaluate_board(a);

        for(size_t i=0;i<moves.size();++i){
            if(time_exceeded()) break;
            const Move &m = moves[i];
            auto nxt=a;
            if(!m.isPass) apply_move(nxt,m,side);

            int nextDepth = depth-1;
            bool explosive = tactical_explosive(a,m,side);
            bool late = (i>=4);
            bool quiet = !explosive;
            bool canReduce = (nextDepth>=2 && late && quiet);

            int R = (canReduce? 1:0);
            int searchDepth = nextDepth - R;

            if(side==me && quiet && nextDepth<=2){
                if(statEval + futility_margin(nextDepth) <= alpha) {
                    continue;
                }
            }

            int val = alphabeta(nxt, searchDepth, alpha, beta, other(side), ply+1, nullptr);
            if(time_up) return evaluate_board(a);

            if(R && side==me && val>alpha && !time_exceeded()){
                val = alphabeta(nxt, nextDepth, alpha, beta, other(side), ply+1, nullptr);
                if(time_up) return evaluate_board(a);
            }

            if(side==me){
                if(val>bestVal){ bestVal=val; bestMv=m; }
                if(bestVal>alpha){
                    alpha=bestVal;
                    if(!m.isPass && ply<MAXD){
                        History[sideIndex(side)][m.x2][m.y2] += (depth*depth);
                        if(!(Killer[ply][0].x1==m.x1 && Killer[ply][0].y1==m.y1 && Killer[ply][0].x2==m.x2 && Killer[ply][0].y2==m.y2)){
                            Killer[ply][1]=Killer[ply][0];
                            Killer[ply][0]=m;
                        }
                    }
                }
                if(alpha>=beta) break;
            }else{
                if(val<bestVal){ bestVal=val; bestMv=m; }
                beta=min(beta,bestVal);
                if(alpha>=beta) break;
            }
        }

        ZobEntry e; e.key=key; e.depth=depth; e.value=bestVal; e.best=bestMv;
        e.flag = (bestVal<=alpha0)?1:((bestVal>=beta0)?2:0);
        TT[key]=e;

        if(bestOut) *bestOut=bestMv;
        return bestVal;
    }

    Move search_iterative(int maxDepth, long long budget_ms){
        time_up=false;
        deadline = chrono::steady_clock::now() + chrono::milliseconds(budget_ms);
        Move best{-1,-1,-1,-1,true};
        int bestVal = evaluate_board(b);
        int aspiration = 60;

        for(int d=1; d<=maxDepth; ++d){
            if(time_exceeded()) break;
            int alpha = bestVal - aspiration;
            int beta  = bestVal + aspiration;
            Move cand;
            int val = alphabeta(b, d, alpha, beta, me, 0, &cand);
            if(time_up) break;

            if(val<=alpha){
                alpha = INT_MIN/4;
                val = alphabeta(b, d, alpha, beta, me, 0, &cand);
            }else if(val>=beta){
                beta = INT_MAX/4;
                val = alphabeta(b, d, alpha, beta, me, 0, &cand);
            }

            if(!cand.isPass){ best=cand; bestVal=val; }
            else{ best=cand; break; }
            aspiration = max(30, aspiration/2 + 10);
        }

        if(best.isPass){
            auto mv=legal_moves(b,me);
            if(!(mv.size()==1 && mv[0].isPass)){
                double sBest=-1e300; Move bm{-1,-1,-1,-1,true};
                for(auto &m: mv){ double s=heuristic_move_score_board(b,me,m); if(s>sBest){sBest=s; bm=m;} }
                best=bm;
            }
        }
        return best;
    }

    // Opening book: 선공 O 대각선 진행 강화, 후공 X 대각 분열 우선
    bool opening_smart(Move &out){
        bool corners = (b[0][0]==O && b[6][6]==O && b[0][6]==X && b[6][0]==X);
        if(!corners) return false;

        int emp=0; for(int r=0;r<N;r++) for(int c=0;c<N;c++) if(b[r][c]==EMPTY) emp++;

        // O: push main diagonal to center as far as possible
        if(me==O){
            if(emp>=45 && b[1][1]==EMPTY){ out={0,0,1,1,false}; return true; }
            if(emp>=44 && b[2][2]==EMPTY && b[1][1]==O){ out={1,1,2,2,false}; return true; }
            if(emp>=43 && b[3][3]==EMPTY && b[2][2]==O){ out={2,2,3,3,false}; return true; }
            if(emp>=42 && b[4][4]==EMPTY && b[3][3]==O){ out={3,3,4,4,false}; return true; }
            if(emp>=41 && b[5][5]==EMPTY && b[4][4]==O){ out={4,4,5,5,false}; return true; }
        }

        // X: diagonal split preference early
        if(me==X){
            if(emp>=44){
                if(b[1][5]==EMPTY){ out={0,6,1,5,false}; return true; }
                if(b[5][1]==EMPTY){ out={6,0,5,1,false}; return true; }
            }
            // 두 번째 단계: 상대가 3,3 혹은 4,4에 도달했을 때 억제
            if(emp>=41){
                // 중앙 4,4 접근 억제 대각견제 후보
                if(b[2][4]==EMPTY && b[0][6]==X){ out={0,6,2,4,false}; return true; }
                if(b[4][2]==EMPTY && b[6][0]==X){ out={6,0,4,2,false}; return true; }
            }
        }
        return false;
    }

    Move choose_move_with_time(long long my_time, long long /*opp_time*/){
        const long long SAFETY = 30; // ms
        long long budget = (long long)min( 1400.0, max( 160.0, my_time*0.085 + 160.0 ) );
        budget = min(budget, max(0LL, my_time - SAFETY));

        if(budget<=0 || my_time<=SAFETY+2){
            auto mv=legal_moves(b,me);
            if(mv.size()==1) return mv[0];
            double best=-1e300; Move bm{-1,-1,-1,-1,true};
            for(auto &m: mv){ double s=heuristic_move_score_board(b,me,m); if(s>best){best=s; bm=m;} }
            return bm;
        }

        Move book;
        if(opening_smart(book)) return book;

        int empties=0; for(int r=0;r<N;r++) for(int c=0;c<N;c++) if(b[r][c]==EMPTY) empties++;
        int maxDepth = (empties<=14? 8 : (empties<=22? 7 : (empties<=32? 6 : 5)));
        if(my_time>8000 && empties>=28) maxDepth++;

        return search_iterative(maxDepth, budget);
    }

    void handle_ready(const string& who){
        if(who=="FIRST"){ me=O; opp=X; }
        else { me=X; opp=O; }
        cout<<"OK\n"; cout.flush();
    }

    void apply_opp_line(int x1,int y1,int x2,int y2){
        if(x1==-1 && y1==-1 && x2==-1 && y2==-1) return;
        Move mv{ x1-1,y1-1,x2-1,y2-1,false };
        apply_move(b,mv,opp);
    }

    void play_turn(long long my_time, long long opp_time){
        Move mv = choose_move_with_time(my_time, opp_time);
        if(mv.isPass){
            cout<<"MOVE -1 -1 -1 -1\n"; cout.flush(); return;
        }
        cout<<"MOVE "<<(mv.x1+1)<<' '<<(mv.y1+1)<<' '<<(mv.x2+1)<<' '<<(mv.y2+1)<<"\n";
        cout.flush();
        apply_move(b,mv,me);
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
        }else if(cmd=="TURN"){
            long long myt, oppt; cin>>myt>>oppt;
            agent.play_turn(myt, oppt);
        }else if(cmd=="OPP"){
            int x1,y1,x2,y2; long long t; cin>>x1>>y1>>x2>>y2>>t;
            agent.apply_opp_line(x1,y1,x2,y2);
        }else if(cmd=="FINISH"){
            break;
        }else{
            string rest; getline(cin, rest);
        }
    }
    return 0;
}
