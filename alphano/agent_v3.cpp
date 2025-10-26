// Ataxx-like 7x7 agent (V3.1): MCTS (UCT) + Progressive Bias + Safer Time Control
// Build: g++ -O2 -std=gnu++17 -s -o agent_v3 agent_v3.cpp
#include <bits/stdc++.h>
using namespace std;

static const int N = 7;
enum Cell : char { EMPTY='.', O='O', X='X' };

struct Move { int x1,y1,x2,y2; bool isPass; };

struct Agent {
    array<array<char,N>,N> b{};
    char me = O, opp = X;

    // Timing
    chrono::steady_clock::time_point deadline;
    inline bool time_up() const { return chrono::steady_clock::now() >= deadline; }

    // RNG
    std::mt19937 rng;
    Agent(): rng(0xC0FFEE ^ (uint64_t)chrono::high_resolution_clock::now().time_since_epoch().count()) {
        reset();
    }

    void reset(){
        for(int i=0;i<N;i++) for(int j=0;j<N;j++) b[i][j]=EMPTY;
        b[0][0]=O; b[6][6]=O;
        b[0][6]=X; b[6][0]=X;
    }

    inline bool inb(int r,int c) const { return 0<=r && r<N && 0<=c && c<N; }
    inline char other(char p) const { return p==O?X:O; }

    // Apply a move
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

    // Legal moves
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

    // Features
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

    // Board evaluation (for rollout cutoff / prior)
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

        int ce = empties(a);

        // Phase weighting
        double phase = 1.0 - (ce/49.0);
        double W_piece = 8.0*phase + 2.0;
        double W_mob   = 10.0*(1.0-phase) + 2.0;
        double W_front = 4.0;
        double W_cent  = 1.5;
        double W_stab  = 2.5;
        double W_reg   = 6.0*phase * 0.0; // skip region in V3.1

        double val = 0.0;
        val += W_piece * piece_diff;
        val += W_mob   * mobility_diff;
        val += W_front * frontier_term;
        val += W_cent  * center;
        val += W_stab  * stab;
        val += W_reg   * 0.0;

        return (int)llround(val);
    }

    // Heuristic ordering/prior
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
        double s = 5.0*fg + 2.0*center + 3.0*stab + 4.0*(d_mob - d_opp_mob) - 3.0*d_front + (d==1?0.08:0.0);
        return s;
    }

    // Smart rollout policy
    Move rollout_policy_pick(const array<array<char,N>,N>& a, char p, vector<Move>& buf) {
        legal_moves_into(a,p,buf);
        if(buf.size()==1) return buf[0]; // PASS or only one
        // Prefer division with >=2 flips
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
        // Fallback to quick score
        double bestScore=-1e300; Move pick=buf[0];
        for(const auto& m: buf){
            double s = quick_move_score(a, p, m);
            if(s>bestScore){ bestScore=s; pick=m; }
        }
        // slight noise
        if(std::uniform_int_distribution<int>(0,14)(rng)==0){
            return buf[ std::uniform_int_distribution<int>(0,(int)buf.size()-1)(rng) ];
        }
        return pick;
    }

    // MCTS Node
    struct Node {
        Move mv;                  // move from parent
        char playerJustMoved;     // who played mv
        int parent=-1;            // index of parent
        vector<int> children;     // indices
        vector<Move> untried;     // moves to expand
        vector<double> priors;    // prior scores (normalized)
        int visits=0;
        double value=0.0;         // sum of results from ROOT(me) perspective
        Node() = default;
    };

    inline double uct_score(const Node& child, int parent_visits, double pbias) const {
        // Progressive bias: add pbias * prior / (1+visits)
        double prior = 0.0;
        if(!child.priors.empty()) prior = child.priors[0]; // store prior in priors[0] for child nodes
        double mean = (child.visits==0)? 0.0 : (child.value/child.visits);
        double uct  = (child.visits==0)? 1e18 : mean + 1.41421356 * sqrt(log((double)parent_visits)/child.visits);
        double bias = pbias * prior / (1.0 + child.visits);
        return uct + bias;
    }

    Move mcts_search(long long budget_ms){
        // Time budget
        deadline = chrono::steady_clock::now() + chrono::milliseconds(budget_ms);

        // Root node
        vector<Node> nodes; nodes.reserve(80000);
        nodes.push_back(Node());
        Node& root = nodes[0];
        root.playerJustMoved = other(me); // to-move = me

        vector<Move> mv = legal_moves(b, me);
        // prune to top-K
        int K = 20;
        sort(mv.begin(), mv.end(), [&](const Move& A, const Move& B){
            return quick_move_score(b, me, A) > quick_move_score(b, me, B);
        });
        if((int)mv.size() > K) mv.resize(K);
        root.untried = mv;
        root.priors.resize(root.untried.size());
        // normalize priors to [0,1]
        double mn=1e300,mx=-1e300;
        for(size_t i=0;i<root.untried.size();++i){
            double s = quick_move_score(b, me, root.untried[i]);
            mn=min(mn,s); mx=max(mx,s);
        }
        for(size_t i=0;i<root.untried.size();++i){
            double s = quick_move_score(b, me, root.untried[i]);
            root.priors[i] = (mx>mn)? (s-mn)/(mx-mn) : 0.5;
        }

        array<array<char,N>,N> state = b;
        vector<Move> mvbuf; mvbuf.reserve(64);

        int iters=0;
        const double PB_ROOT = 0.8;   // progressive bias strength at root
        const double PB_NODE = 0.5;   // and internal nodes

        while(!time_up()){
            ++iters;
            // 1) Selection
            int n = 0;
            state = b;
            char side = me;
            vector<int> path; path.reserve(256);
            path.push_back(n);

            while(nodes[n].untried.empty() && !nodes[n].children.empty()){
                // pick best child by UCT + progressive bias
                int bestChild=-1; double best=-1e300;
                for(int ci: nodes[n].children){
                    double s = uct_score(nodes[ci], nodes[n].visits, (n==0?PB_ROOT:PB_NODE));
                    if(s>best){ best=s; bestChild=ci; }
                }
                n = bestChild;
                path.push_back(n);
                // play child move
                if(!nodes[n].mv.isPass) apply_move(state, nodes[n].mv, side);
                side = other(side);
                if(time_up()) break;
            }
            if(time_up()) break;

            // 2) Expansion
            if(!nodes[n].untried.empty()){
                // pick the untried with highest prior
                int pickIdx = 0; double best=-1e300;
                for(size_t i=0;i<nodes[n].untried.size();++i){
                    double s = quick_move_score(state, side, nodes[n].untried[i]);
                    if(s>best){ best=s; pickIdx=(int)i; }
                }
                Move m = nodes[n].untried[pickIdx];
                // apply
                if(!m.isPass) apply_move(state, m, side);

                // create child
                Node child;
                child.mv = m;
                child.playerJustMoved = side;
                child.parent = n;
                // child untried
                vector<Move> next = legal_moves(state, other(side));
                // prune K
                sort(next.begin(), next.end(), [&](const Move& A, const Move& B){
                    return quick_move_score(state, other(side), A) > quick_move_score(state, other(side), B);
                });
                if((int)next.size()>K) next.resize(K);
                child.untried = next;
                // set prior into child.priors[0] for bias
                child.priors = { 0.0 };
                child.priors[0] = (best>0? 1.0 : 0.3); // crude mapping

                // remove from parent's untried
                nodes[n].untried.erase(nodes[n].untried.begin()+pickIdx);
                // push child
                nodes[n].children.push_back((int)nodes.size());
                nodes.push_back(std::move(child));

                n = (int)nodes.size()-1;
                path.push_back(n);
                side = other(side);
            }

            if(time_up()) break;

            // 3) Simulation (rollout) from 'state' with side to move = side
            double result = 0.5;
            {
                int steps=0;
                int pass_streak=0;
                array<array<char,N>,N> s = state;
                char turn = side;
                while(steps < 60){ // shorter rollout for more iters
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
                if(co==0 && cx==0){
                    result = 0.5;
                } else if(co==0){
                    result = (me==O)? 0.0 : 1.0;
                } else if(cx==0){
                    result = (me==O)? 1.0 : 0.0;
                } else if(empties(s)==0){
                    int myc = (me==O?co:cx);
                    int opc = (me==O?cx:co);
                    result = (myc>opc)?1.0: (myc<opc?0.0:0.5);
                } else {
                    int eval = evaluate_board(s);
                    double k = 0.03; // slightly steeper
                    double sig = 1.0 / (1.0 + exp(-k * eval));
                    result = sig;
                }
            }

            // 4) Backprop
            for(int idx : path){
                nodes[idx].visits += 1;
                nodes[idx].value  += result;
            }
        }

        // Choose move: highest visit count; tie-break by winrate
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

    // Protocol helpers
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
        // Strong safety: if 잔여시간 < 200ms → 탐색 생략, 즉시 그리디
        if(my_time < 200){
            vector<Move> moves = legal_moves(b, me);
            if(moves.size()==1) return moves[0];
            double best=-1e300; Move pick=moves[0];
            for(auto &m: moves){ double s=quick_move_score(b, me, m); if(s>best){best=s; pick=m;} }
            return pick;
        }
        // Conservative budget: min(800ms, 0.05*my_time + 100ms), leave 20ms margin
        long long budget = (long long)min( 800.0, max( 120.0, my_time*0.05 + 100.0 ) );
        budget = min(budget, max(0LL, my_time - 20));
        deadline = chrono::steady_clock::now() + chrono::milliseconds(max(1LL,budget));

        vector<Move> rootMoves = legal_moves(b, me);
        if(rootMoves.size()==1 && rootMoves[0].isPass) return rootMoves[0];

        Move mv = mcts_search(budget);
        // Fallback: pick best quick score if pass returned but moves exist
        if(mv.isPass && !(rootMoves.size()==1 && rootMoves[0].isPass)){
            double best=-1e300; Move pick=rootMoves[0];
            for(auto &m: rootMoves){
                double s = quick_move_score(b, me, m);
                if(s>best){ best=s; pick=m; }
            }
            mv = pick;
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
