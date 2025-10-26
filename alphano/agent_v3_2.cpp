// Ataxx-like 7x7 agent (V3.5): MCTS + Opponent-aware scoring + Endgame Alpha-Beta
// Changes from V3.4:
// - Removed early cheap_greedy shortcut (caused 1ms openings). Always allocate real budget.
// - Small opening book (safe center divisions/leaps) for first move patterns.
// - Slightly higher early budgets; AB trigger at empties<=16 with adaptive depth.
// Build: g++ -O2 -std=gnu++17 -s -o agent_v3 agent_v3.cpp
#include <bits/stdc++.h>
using namespace std;

static const int N = 7;
enum Cell : char { EMPTY='.', O='O', X='X' };

struct Move { int x1,y1,x2,y2; bool isPass; };

struct Agent {
    array<array<char,N>,N> b{};
    char me = O, opp = X;

    chrono::steady_clock::time_point deadline;
    inline bool time_up() const { return chrono::steady_clock::now() >= deadline; }

    std::mt19937 rng;
    Agent(): rng(0xDEADBEEF ^ (uint64_t)chrono::high_resolution_clock::now().time_since_epoch().count()) {
        reset();
    }

    void reset(){
        for(int i=0;i<N;i++) for(int j=0;j<N;j++) b[i][j]=EMPTY;
        b[0][0]=O; b[6][6]=O;
        b[0][6]=X; b[6][0]=X;
    }

    inline bool inb(int r,int c) const { return 0<=r && r<N && 0<=c && c<N; }
    inline char other(char p) const { return p==O?X:O; }

    inline void apply_move(array<array<char,N>,N>& a, const Move& mv, char p) const {
        if(mv.isPass) return;
        int d = max(abs(mv.x1-mv.x2), abs(mv.y1-mv.y2));
        if(d==1){
            a[mv.x2][mv.y2] = p;
        }else{
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

    inline void legal_moves_into(const array<array<char,N>,N>& a, char p, vector<Move>& out) const {
        out.clear();
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
                        if(d==1 || d==2) out.push_back({r,c,nr,nc,false});
                    }
                }
            }
        }
        if(out.empty()) out.push_back({-1,-1,-1,-1,true});
    }
    inline vector<Move> legal_moves(const array<array<char,N>,N>& a, char p) const {
        vector<Move> v; v.reserve(64);
        legal_moves_into(a,p,v);
        return v;
    }

    Move first_legal_prefer_division(const array<array<char,N>,N>& a, char p){
        for(int r=0;r<N;r++){
            for(int c=0;c<N;c++){
                if(a[r][c]!=p) continue;
                for(int dr=-1; dr<=1; ++dr){
                    for(int dc=-1; dc<=1; ++dc){
                        if(dr==0 && dc==0) continue;
                        int nr=r+dr, nc=c+dc;
                        if(inb(nr,nc) && a[nr][nc]==EMPTY){
                            return Move{r,c,nr,nc,false};
                        }
                    }
                }
            }
        }
        for(int r=0;r<N;r++){
            for(int c=0;c<N;c++){
                if(a[r][c]!=p) continue;
                for(int dr=-2; dr<=2; ++dr){
                    for(int dc=-2; dc<=2; ++dc){
                        if(max(abs(dr),abs(dc))!=2) continue;
                        int nr=r+dr, nc=c+dc;
                        if(inb(nr,nc) && a[nr][nc]==EMPTY){
                            return Move{r,c,nr,nc,false};
                        }
                    }
                }
            }
        }
        return Move{-1,-1,-1,-1,true};
    }

    Move cheap_greedy(const array<array<char,N>,N>& a, char p){
        vector<Move> mv; mv.reserve(64); legal_moves_into(a,p,mv);
        if(mv.size()==1) return mv[0];
        double best=-1e300; Move pick=mv[0];
        for(const auto& m: mv){
            if(m.isPass) continue;
            int fg=0;
            for(int dr=-1; dr<=1; ++dr) for(int dc=-1; dc<=1; ++dc){
                if(dr==0 && dc==0) continue;
                int nr=m.x2+dr, nc=m.y2+dc;
                if(inb(nr,nc) && a[nr][nc]!=EMPTY && a[nr][nc]!=p) fg++;
            }
            int center = 3 - max(abs(m.x2-3), abs(m.y2-3));
            bool corner = ((m.x2==0||m.x2==6) && (m.y2==0||m.y2==6));
            bool edge = (m.x2==0||m.x2==6||m.y2==0||m.y2==6);
            int d = max(abs(m.x1-m.x2), abs(m.y1-m.y2));
            double s = 5.0*fg + 2.2*center + (corner? 2.0 : (edge?0.6:0.0)) + (d==1?0.08:0.0);
            if(s>best){ best=s; pick=m; }
        }
        return pick;
    }

    inline pair<int,int> counts(const array<array<char,N>,N>& a) const {
        int co=0,cx=0;
        for(int r=0;r<N;r++) for(int c=0;c<N;c++){
            if(a[r][c]==O) co++; else if(a[r][c]==X) cx++;
        }
        return {co,cx};
    }
    inline int empties(const array<array<char,N>,N>& a) const {
        int ce=0; for(int r=0;r<N;r++) for(int c=0;c<N;c++) if(a[r][c]==EMPTY) ce++; return ce;
    }
    inline int center_bonus_cell(int r,int c) const {
        int dist = max(abs(r-3), abs(c-3));
        return 3 - dist; // [3..0]
    }
    inline int stability_bonus_cell(int r,int c) const {
        bool corner = ((r==0||r==6) && (c==0||c==6));
        if(corner) return 2;
        bool edge = (r==0||r==6||c==0||c==6);
        return edge?1:0;
    }
    inline int flip_gain_if_place(const array<array<char,N>,N>& a, int r,int c, char p) const {
        int flips=0;
        for(int dr=-1; dr<=1; ++dr) for(int dc=-1; dc<=1; ++dc){
            if(dr==0 && dc==0) continue;
            int nr=r+dr, nc=c+dc;
            if(inb(nr,nc) && a[nr][nc]!=EMPTY && a[nr][nc]!=p) flips++;
        }
        return flips;
    }
    int mobility(const array<array<char,N>,N>& a, char p) const {
        vector<Move> v; v.reserve(64); legal_moves_into(a,p,v);
        return (v.size()==1 && v[0].isPass)?0:(int)v.size();
    }
    int frontier_count(const array<array<char,N>,N>& a, char p) const {
        char q = other(p);
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

    int evaluate_board_me(const array<array<char,N>,N>& a) const {
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
        int ce = empties(a);

        double phase = 1.0 - (ce/49.0);
        double W_piece = 8.0*phase + 2.0;
        double W_mob   = 10.0*(1.0-phase) + 2.0;
        double W_front = 4.0;
        double W_cent  = 1.6;
        double W_stab  = 2.6;

        double val = 0.0;
        val += W_piece * piece_diff;
        val += W_mob   * mobility_diff;
        val += W_front * frontier_term;
        val += W_cent  * center;
        val += W_stab  * stab;

        return (int)llround(val);
    }

    // Opponent-aware quick score
    double quick_move_score(const array<array<char,N>,N>& a, char p, const Move& mv) const {
        if(mv.isPass) return -1e9;
        int fg = flip_gain_if_place(a, mv.x2, mv.y2, p);
        int center = center_bonus_cell(mv.x2, mv.y2);
        int stab   = stability_bonus_cell(mv.x2, mv.y2);
        int d = max(abs(mv.x1-mv.x2), abs(mv.y1-mv.y2));

        auto after = a; apply_move(after, mv, p);
        int d_mob = mobility(after,p) - mobility(a,p);
        int d_opp_mob = mobility(after,other(p)) - mobility(a,other(p));
        int d_front = frontier_count(after,p) - frontier_count(a,p);

        vector<Move> oppmv; oppmv.reserve(64); legal_moves_into(after, other(p), oppmv);
        int opp_best_fg = 0;
        if(!(oppmv.size()==1 && oppmv[0].isPass)){
            for(const auto& om: oppmv){
                if(om.isPass) continue;
                opp_best_fg = max(opp_best_fg, flip_gain_if_place(after, om.x2, om.y2, other(p)));
            }
        }

        int emp = empties(a);
        double anti = (emp>=32 ? 2.2 : emp>=18 ? 1.5 : 0.9);

        double s = 5.0*fg + 2.2*center + 3.0*stab + 4.0*(d_mob - d_opp_mob) - 3.2*d_front
                   - anti * opp_best_fg + (d==1?0.12:0.0);
        return s;
    }

    Move rollout_policy_pick(const array<array<char,N>,N>& a, char p, vector<Move>& buf) {
        legal_moves_into(a,p,buf);
        if(buf.size()==1) return buf[0];
        Move best{0,0,0,0,true}; int best_fg=-1; bool has=false;
        for(const auto& m: buf){
            if(m.isPass) continue;
            int fg = flip_gain_if_place(a, m.x2, m.y2, p);
            int d = max(abs(m.x1-m.x2), abs(m.y1-m.y2));
            if(d==1 && fg>=2){
                if(fg>best_fg){ best_fg=fg; best=m; has=true; }
            }
        }
        if(has) return best;
        double bestScore=-1e300; Move pick=buf[0];
        for(const auto& m: buf){
            double s = quick_move_score(a, p, m);
            if(s>bestScore){ bestScore=s; pick=m; }
        }
        if(std::uniform_int_distribution<int>(0,17)(rng)==0){
            return buf[ std::uniform_int_distribution<int>(0,(int)buf.size()-1)(rng) ];
        }
        return pick;
    }

    // ---------------- Endgame Alpha-Beta ----------------
    struct TTEntry { int depth; int val; int8_t flag; Move best; }; // flag: 0=exact, -1=upper, 1=lower
    unordered_map<uint64_t, TTEntry> TT;

    uint64_t hash_board(const array<array<char,N>,N>& a, char toMove) const {
        uint64_t h=1469598103934665603ull;
        for(int r=0;r<N;r++) for(int c=0;c<N;c++){
            h ^= (uint64_t)a[r][c] + 0x100*(r*7+c); h *= 1099511628211ull;
        }
        h ^= (uint64_t)toMove * 0x9e3779b97f4a7c15ull;
        return h;
    }

    int negamax(array<array<char,N>,N>& a, char toMove, int depth, int alpha, int beta){
        if(time_up()) return evaluate_board_me(a);
        auto [co,cx] = counts(a);
        if(co==0 || cx==0 || empties(a)==0 || depth==0){
            return evaluate_board_me(a);
        }
        uint64_t h = hash_board(a, toMove);
        auto it = TT.find(h);
        if(it!=TT.end() && it->second.depth>=depth){
            const TTEntry &e = it->second;
            if(e.flag==0) return e.val;
            else if(e.flag<0) beta = min(beta, e.val);
            else alpha = max(alpha, e.val);
            if(alpha>=beta) return e.val;
        }

        vector<Move> mv; mv.reserve(64); legal_moves_into(a,toMove,mv);
        if(mv.size()==1 && mv[0].isPass){
            vector<Move> oppmv; oppmv.reserve(64); legal_moves_into(a,other(toMove),oppmv);
            if(oppmv.size()==1 && oppmv[0].isPass){
                return evaluate_board_me(a);
            }
            int val = -negamax(a, other(toMove), depth-1, -beta, -alpha);
            return val;
        }

        sort(mv.begin(), mv.end(), [&](const Move& A, const Move& B){
            return quick_move_score(a, toMove, A) > quick_move_score(a, toMove, B);
        });

        int bestVal = INT_MIN/4;
        Move bestMove = mv[0];
        int alpha0 = alpha;

        for(const auto& m: mv){
            array<array<char,N>,N> a2 = a;
            if(!m.isPass) apply_move(a2, m, toMove);
            int v = -negamax(a2, other(toMove), depth-1, -beta, -alpha);
            if(v>bestVal){ bestVal=v; bestMove=m; }
            if(v>alpha) alpha=v;
            if(alpha>=beta) break;
            if(time_up()) break;
        }

        int8_t fl = (bestVal<=alpha0)? -1 : (bestVal>=beta? 1:0);
        TT[h] = TTEntry{ depth, bestVal, fl, bestMove };
        return bestVal;
    }

    pair<Move,int> ab_decide(long long budget_ms, int depth){
        deadline = chrono::steady_clock::now() + chrono::milliseconds(budget_ms);
        TT.reserve(1<<18);
        TT.max_load_factor(0.7f);
        vector<Move> root; root.reserve(64); legal_moves_into(b, me, root);
        if(root.size()==1) return {root[0], 0};
        sort(root.begin(), root.end(), [&](const Move& A, const Move& B){
            return quick_move_score(b, me, A) > quick_move_score(b, me, B);
        });
        int alpha = INT_MIN/4, beta = INT_MAX/4;
        Move best = root[0];
        int bestV = INT_MIN/4;
        for(const auto& m: root){
            array<array<char,N>,N> s = b;
            if(!m.isPass) apply_move(s, m, me);
            int v = -negamax(s, opp, depth-1, -beta, -alpha);
            if(v>bestV){ bestV=v; best=m; }
            if(v>alpha) alpha=v;
            if(time_up()) break;
        }
        return {best, bestV};
    }

    struct Node {
        Move mv; char playerJustMoved; int parent=-1;
        vector<int> children; vector<Move> untried; vector<double> priors;
        int visits=0; double value=0.0;
    };
    inline double uct_score(const Node& child, int parent_visits, double pbias) const {
        double prior = 0.0;
        if(!child.priors.empty()) prior = child.priors[0];
        double mean = (child.visits==0)? 0.0 : (child.value/child.visits);
        double uct  = (child.visits==0)? 1e18 : mean + 1.41421356 * sqrt(log((double)parent_visits)/child.visits);
        double bias = pbias * prior / (1.0 + child.visits);
        return uct + bias;
    }

    Move mcts_search(long long budget_ms, int K_root, int K_node, int rollout_cap){
        deadline = chrono::steady_clock::now() + chrono::milliseconds(budget_ms);

        vector<Node> nodes; nodes.reserve(150000);
        nodes.push_back(Node());
        Node& root = nodes[0];
        root.playerJustMoved = other(me);

        vector<Move> mv = legal_moves(b, me);
        vector<pair<double,int>> scored; scored.reserve(mv.size());
        double mn=1e300,mx=-1e300;
        for(size_t i=0;i<mv.size();++i){
            double s = quick_move_score(b, me, mv[i]);
            scored.push_back({s,(int)i});
            mn=min(mn,s); mx=max(mx,s);
        }
        sort(scored.begin(), scored.end(), [](const auto& A, const auto& B){ return A.first>B.first; });
        int keep = min((int)mv.size(), K_root);
        root.untried.reserve(keep); root.priors.reserve(keep);
        for(int i=0;i<keep;i++){
            root.untried.push_back(mv[scored[i].second]);
            double s = scored[i].first;
            double pr = (mx>mn)? (s-mn)/(mx-mn) : 0.5;
            root.priors.push_back(pr);
        }

        array<array<char,N>,N> state = b;
        vector<Move> mvbuf; mvbuf.reserve(64);
        const double PB_ROOT = 0.7, PB_NODE = 0.45;

        while(!time_up()){
            int n = 0;
            state = b;
            char side = me;
            vector<int> path; path.reserve(256);
            path.push_back(n);

            while(nodes[n].untried.empty() && !nodes[n].children.empty()){
                int bestChild=-1; double best=-1e300;
                for(int ci: nodes[n].children){
                    double s = uct_score(nodes[ci], nodes[n].visits, (n==0?PB_ROOT:PB_NODE));
                    if(s>best){ best=s; bestChild=ci; }
                }
                n = bestChild;
                path.push_back(n);
                if(!nodes[n].mv.isPass) apply_move(state, nodes[n].mv, side);
                side = other(side);
                if(time_up()) break;
            }
            if(time_up()) break;

            if(!nodes[n].untried.empty()){
                int pickIdx = 0; double best=-1e300;
                for(size_t i=0;i<nodes[n].untried.size();++i){
                    double s = quick_move_score(state, side, nodes[n].untried[i]);
                    if(s>best){ best=s; pickIdx=(int)i; }
                }
                Move m = nodes[n].untried[pickIdx];
                if(!m.isPass) apply_move(state, m, side);

                Node child; child.mv=m; child.playerJustMoved=side; child.parent=n;
                vector<Move> next; next.reserve(64); legal_moves_into(state, other(side), next);
                if((int)next.size()>K_node){
                    vector<pair<double,int>> sc; sc.reserve(next.size());
                    for(size_t i=0;i<next.size();++i){
                        sc.push_back({quick_move_score(state, other(side), next[i]), (int)i});
                    }
                    nth_element(sc.begin(), sc.begin()+K_node, sc.end(), [](const auto& A, const auto& B){ return A.first>B.first; });
                    sort(sc.begin(), sc.begin()+K_node, [](const auto& A, const auto& B){ return A.first>B.first; });
                    vector<Move> keepv; keepv.reserve(K_node);
                    for(int i=0;i<K_node;i++) keepv.push_back(next[sc[i].second]);
                    child.untried.swap(keepv);
                }else child.untried = next;
                child.priors = { (best>0? 1.0 : 0.3) };

                nodes[n].untried.erase(nodes[n].untried.begin()+pickIdx);
                nodes[n].priors.erase(nodes[n].priors.begin()+pickIdx);
                nodes[n].children.push_back((int)nodes.size());
                nodes.push_back(std::move(child));

                n = (int)nodes.size()-1;
                path.push_back(n);
                side = other(side);
            }

            if(time_up()) break;

            double result = 0.5;
            {
                int steps=0, pass_streak=0;
                array<array<char,N>,N> s = state;
                char turn = side;
                while(steps < rollout_cap){
                    mvbuf.clear();
                    legal_moves_into(s, turn, mvbuf);
                    if(mvbuf.size()==1 && mvbuf[0].isPass){
                        pass_streak++;
                        if(pass_streak>=2) break;
                        turn = other(turn);
                        steps++;
                        continue;
                    } else pass_streak=0;
                    Move rm = rollout_policy_pick(s, turn, mvbuf);
                    if(!rm.isPass) apply_move(s, rm, turn);
                    turn = other(turn);
                    steps++;
                    auto [co,cx] = counts(s);
                    if(co==0 || cx==0 || empties(s)==0) break;
                    if(time_up()) break;
                }
                auto [co,cx] = counts(s);
                if(co==0 && cx==0) result = 0.5;
                else if(co==0) result = (me==O)? 0.0 : 1.0;
                else if(cx==0) result = (me==O)? 1.0 : 0.0;
                else if(empties(s)==0){
                    int myc = (me==O?co:cx), opc = (me==O?cx:co);
                    result = (myc>opc)?1.0: (myc<opc?0.0:0.5);
                } else {
                    int eval = evaluate_board_me(s);
                    double k = 0.03;
                    double sig = 1.0 / (1.0 + exp(-k * eval));
                    result = sig;
                }
            }

            for(int idx : path){
                nodes[idx].visits += 1;
                nodes[idx].value  += result;
            }
        }

        if(nodes[0].children.empty()){
            if(!nodes[0].untried.empty()) return nodes[0].untried[0];
            return { -1,-1,-1,-1,true };
        }
        int bestChild = nodes[0].children.front();
        int bestV = nodes[bestChild].visits;
        double bestWR = nodes[bestChild].visits? nodes[bestChild].value/nodes[bestChild].visits : 0.0;
        for(int ci: nodes[0].children){
            int v = nodes[ci].visits;
            double wr = v? nodes[ci].value/v : 0.0;
            if(v>bestV || (v==bestV && wr>bestWR)){
                bestV=v; bestWR=wr; bestChild=ci;
            }
        }
        return nodes[bestChild].mv;
    }

    // -------- Opening book (very small, safe centers) --------
    bool is_initial_board_for_O() const {
        // All four corners occupied, rest empty
        if(b[0][0]!=O || b[6][6]!=O || b[0][6]!=X || b[6][0]!=X) return false;
        for(int r=0;r<N;r++) for(int c=0;c<N;c++){
            if((r==0&&c==0)||(r==6&&c==6)||(r==0&&c==6)||(r==6&&c==0)) continue;
            if(b[r][c]!=EMPTY) return false;
        }
        return true;
    }
    optional<Move> opening_book(){
        vector<Move> mv; mv.reserve(64); legal_moves_into(b, me, mv);
        if(me==O && is_initial_board_for_O()){
            // Prefer (1,1)->(2,2) if legal, else (7,7)->(6,6), else fallback
            for(const auto&m: mv){
                if(!m.isPass && m.x1==0 && m.y1==0 && m.x2==1 && m.y2==1) return m;
            }
            for(const auto&m: mv){
                if(!m.isPass && m.x1==6 && m.y1==6 && m.x2==5 && m.y2==5) return m;
            }
        }
        // If opponent just did (1,7)->(1,6), reply by centralizing
        // i.e., take (2,2) or (3,3) if available
        if(me==X){
            // if our OPP line likely was (1,7)->(1,6) or (2,6)
            // simple heuristic: if b[0][5]==X and center empty, go (2,2) from (1,1) if we own it (we don't, we're X) -> skip
            // So for X no strict book; rely on search.
        }
        return {};
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
        // Ultra-low time guards
        if(my_time <= 20){
            return first_legal_prefer_division(b, me);
        }
        if(my_time <= 120){
            return cheap_greedy(b, me);
        }

        // Tiny opening book
        if(auto mb = opening_book(); mb.has_value()){
            return mb.value();
        }

        int emp = empties(b);
        bool doAB = (emp <= 16);
        int expected_own = max(1, (emp + 5) / 2);
        int phase_cap = (emp > 28 ? 700 : emp > 16 ? 540 : 320);
        long long budget = (long long) min( (double)phase_cap, 0.92 * (double)my_time / (double)expected_own );
        budget = max( (long long)200, budget);
        budget = min(budget, max(0LL, my_time - 45));
        deadline = chrono::steady_clock::now() + chrono::milliseconds(max(1LL,budget));

        vector<Move> rootMoves = legal_moves(b, me);
        if(rootMoves.size()==1 && rootMoves[0].isPass) return rootMoves[0];

        if(doAB){
            int depth;
            if(emp >= 14) depth = 4;
            else if(emp >= 10) depth = 6;
            else depth = 7;
            auto [mv, val] = ab_decide(budget, depth);
            if(!(mv.isPass && !(rootMoves.size()==1 && rootMoves[0].isPass))){
                return mv;
            }
        }

        int K_root = std::clamp(22 + emp/6, 22, 34);
        int K_node = std::clamp(12 + emp/8, 12, 26);
        int rollout_cap = (my_time > 2400 ? 88 : my_time > 1000 ? 76 : 60);
        if(emp < 10) rollout_cap = min(rollout_cap, 46);

        Move mv = mcts_search(budget, K_root, K_node, rollout_cap);
        if(mv.isPass && !(rootMoves.size()==1 && rootMoves[0].isPass)){
            mv = cheap_greedy(b, me);
        }
        return mv;
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
