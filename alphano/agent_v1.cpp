// Ataxx-like 7x7 agent (V1 heuristic-only, no search)
// Protocol: READY / TURN / OPP / FINISH
// Build: g++ -O2 -std=gnu++17 -static -s -o agent agent_v1.cpp  (or without -static on some judges)
#include <bits/stdc++.h>
using namespace std;

static const int N = 7;
enum Cell : char { EMPTY='.', O='O', X='X' };

struct Move {
    int x1,y1,x2,y2; // 0-based internal
    bool isPass;
};

struct Agent {
    // Board is row-major, 0..6
    array<array<char,N>,N> b{};
    char me = O, opp = X;
    bool initialized = false;

    Agent(){ reset(); }

    void reset(){
        for(int i=0;i<N;i++) for(int j=0;j<N;j++) b[i][j]=EMPTY;
        b[0][0]=O; b[6][6]=O;
        b[0][6]=X; b[6][0]=X;
        initialized = true;
    }

    inline bool inb(int r,int c) const { return 0<=r && r<N && 0<=c && c<N; }

    // Apply a move for player p on a COPY board
    void apply_move(array<array<char,N>,N>& a, const Move& mv, char p) const {
        if(mv.isPass) return;
        int d = max(abs(mv.x1-mv.x2), abs(mv.y1-mv.y2));
        if(d==1){
            // Division: source stays, dest becomes p
            a[mv.x2][mv.y2] = p;
        }else if(d==2){
            // Leap: source becomes empty, dest becomes p
            a[mv.x2][mv.y2] = p;
            a[mv.x1][mv.y1] = EMPTY;
        }
        // Infection around dest (8-neighbor)
        for(int dr=-1; dr<=1; ++dr){
            for(int dc=-1; dc<=1; ++dc){
                if(dr==0 && dc==0) continue;
                int nr = mv.x2 + dr, nc = mv.y2 + dc;
                if(inb(nr,nc) && a[nr][nc] != EMPTY && a[nr][nc] != p){
                    a[nr][nc] = p;
                }
            }
        }
    }

    // Flip gain at dest on board a if p moves there
    int flip_gain_if_place(const array<array<char,N>,N>& a, int r, int c, char p) const {
        int flips = 0;
        for(int dr=-1; dr<=1; ++dr){
            for(int dc=-1; dc<=1; ++dc){
                if(dr==0 && dc==0) continue;
                int nr=r+dr, nc=c+dc;
                if(inb(nr,nc) && a[nr][nc] != EMPTY && a[nr][nc] != p) flips++;
            }
        }
        return flips;
    }

    // List all legal moves for player p on board a
    vector<Move> legal_moves(const array<array<char,N>,N>& a, char p) const {
        vector<Move> mv;
        for(int r=0;r<N;r++){
            for(int c=0;c<N;c++){
                if(a[r][c] != p) continue;
                for(int dr=-2; dr<=2; ++dr){
                    for(int dc=-2; dc<=2; ++dc){
                        if(dr==0 && dc==0) continue;
                        int nr = r+dr, nc = c+dc;
                        if(!inb(nr,nc)) continue;
                        if(a[nr][nc] != EMPTY) continue;
                        int d = max(abs(dr),abs(dc));
                        if(d==1 || d==2){
                            mv.push_back({r,c,nr,nc,false});
                        }
                    }
                }
            }
        }
        if(mv.empty()){
            mv.push_back({-1,-1,-1,-1,true}); // PASS
        }
        return mv;
    }

    // Mobility: number of legal moves for p
    int mobility(const array<array<char,N>,N>& a, char p) const {
        auto mv = legal_moves(a, p);
        if(mv.size()==1 && mv[0].isPass) return 0;
        return (int)mv.size();
    }

    // Frontier count: number of p's pieces that are adjacent to any opponent piece
    int frontier_count(const array<array<char,N>,N>& a, char p) const {
        char q = (p==O?X:O);
        int cnt=0;
        for(int r=0;r<N;r++){
            for(int c=0;c<N;c++){
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
        }
        return cnt;
    }

    // Count pieces
    pair<int,int> counts(const array<array<char,N>,N>& a) const {
        int co=0, cx=0;
        for(int r=0;r<N;r++) for(int c=0;c<N;c++){
            if(a[r][c]==O) co++;
            else if(a[r][c]==X) cx++;
        }
        return {co,cx};
    }

    // Center bonus for a target cell (closer to center is better)
    int center_bonus_cell(int r,int c) const {
        // Use Chebyshev distance to center (3,3)
        int dist = max(abs(r-3), abs(c-3));
        // Closer → higher bonus; map dist in [0..3] to [3..0]
        return 3 - dist; // 3 for center, 2 for ring1, 1 for ring2, 0 for corners ring
    }

    // Stability bonus: corner +2, edge +1
    int stability_bonus_cell(int r,int c) const {
        bool corner = ( (r==0||r==6) && (c==0||c==6) );
        if(corner) return 2;
        bool edge = (r==0||r==6||c==0||c==6);
        return edge ? 1 : 0;
    }

    // Region parity bonus (simple endgame heuristic):
    // For empty cells, 8-neighbor connected components:
    //   bonus = (#odd_components - #even_components)
    int region_parity_bonus(const array<array<char,N>,N>& a) const {
        vector<vector<int>> vis(N, vector<int>(N,0));
        int odd=0, even=0;
        const int drs[8]={-1,-1,-1,0,0,1,1,1};
        const int dcs[8]={-1,0,1,-1,1,-1,0,1};
        for(int r=0;r<N;r++) for(int c=0;c<N;c++){
            if(a[r][c]!=EMPTY || vis[r][c]) continue;
            // BFS
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

    // Heuristic evaluation of a single move from current board b for player 'me'
    // Returns score and captures features for debugging if needed.
    double evaluate_move(const Move& mv) const {
        if(mv.isPass) return -1e9; // avoid pass unless forced

        // Current stats
        int my_frontier_before = frontier_count(b, me);
        int my_mob_before = mobility(b, me);
        int opp_mob_before = mobility(b, opp);

        // Make a copy and apply move
        auto after = b;
        // Flip gain from destination on current board (before infection applied)
        int fg = flip_gain_if_place(b, mv.x2, mv.y2, me);
        // Apply move fully
        apply_move(after, mv, me);

        // After-move stats
        int my_frontier_after = frontier_count(after, me);
        int my_mob_after = mobility(after, me);
        int opp_mob_after = mobility(after, opp);

        int d_frontier = my_frontier_after - my_frontier_before;
        int d_mobility = (my_mob_after - my_mob_before) - (opp_mob_after - opp_mob_before);

        int center_b = center_bonus_cell(mv.x2, mv.y2);
        int stab_b = stability_bonus_cell(mv.x2, mv.y2);

        // Region parity only when empties are small (endgame-ish)
        int empties = 0;
        for(int r=0;r<N;r++) for(int c=0;c<N;c++) if(after[r][c]==EMPTY) empties++;
        int region_b = 0;
        if(empties <= 10) region_b = region_parity_bonus(after);

        // Weights (tuned conservatively)
        const double W_flip_gain   = 5.0;
        const double W_d_mobility  = 7.0;
        const double W_d_frontier  = -4.0; // penalty when frontier increases
        const double W_center      = 2.0;
        const double W_stability   = 3.0;
        const double W_region      = 6.0;

        double score = 0.0;
        score += W_flip_gain  * fg;
        score += W_d_mobility * d_mobility;
        score += W_d_frontier * d_frontier;
        score += W_center     * center_b;
        score += W_stability  * stab_b;
        score += W_region     * region_b;

        // Tiebreak nudges
        int d = max(abs(mv.x1-mv.x2), abs(mv.y1-mv.y2));
        // Prefer division (safer) if similar score
        score += (d==1 ? 0.05 : 0.0);
        // Prefer connecting near own stones (mild): count adjacent friendly at dest
        int adj_friend=0;
        for(int dr=-1; dr<=1; ++dr) for(int dc=-1; dc<=1; ++dc){
            if(dr==0 && dc==0) continue;
            int nr=mv.x2+dr, nc=mv.y2+dc;
            if(inb(nr,nc) && b[nr][nc]==me) adj_friend++;
        }
        score += 0.03 * adj_friend;

        return score;
    }

    Move choose_move(){
        auto moves = legal_moves(b, me);
        if(moves.size()==1 && moves[0].isPass) return moves[0];

        // Order candidates: prioritize high flip gain divisions first, then others
        struct Cand { Move mv; double key; int flip; int dist; };
        vector<Cand> cand;
        cand.reserve(moves.size());
        for(auto &mv: moves){
            int d = max(abs(mv.x1-mv.x2), abs(mv.y1-mv.y2));
            int flip = flip_gain_if_place(b, mv.x2, mv.y2, me);
            double key = (d==1 ? 1000 : 0) + flip; // simple ordering key
            cand.push_back({mv,key,flip,d});
        }
        stable_sort(cand.begin(), cand.end(),
                    [](const Cand& A, const Cand& B){
                        if (A.key!=B.key) return A.key > B.key;
                        // prefer center
                        int Acenter = max(abs(A.mv.x2-3), abs(A.mv.y2-3));
                        int Bcenter = max(abs(B.mv.x2-3), abs(B.mv.y2-3));
                        if (Acenter!=Bcenter) return Acenter < Bcenter;
                        // prefer division
                        if (A.dist!=B.dist) return A.dist < B.dist;
                        return false;
                    });

        // Evaluate all (small board → cheap)
        double bestScore = -1e300;
        Move best = { -1,-1,-1,-1,true };
        for(auto &c : cand){
            double s = evaluate_move(c.mv);
            if(s > bestScore){
                bestScore = s;
                best = c.mv;
            }
        }
        return best;
    }

    // Protocol helpers
    void handle_ready(const string& who){
        if(who=="FIRST"){ me=O; opp=X; }
        else { me=X; opp=O; }
        cout << "OK" << endl;
        cout.flush();
    }

    void apply_opp_line(int x1,int y1,int x2,int y2){
        if(x1==-1 && y1==-1 && x2==-1 && y2==-1){
            // PASS
            return;
        }
        // Convert to 0-based
        Move mv;
        mv.x1 = x1-1; mv.y1=y1-1; mv.x2=x2-1; mv.y2=y2-1; mv.isPass=false;
        apply_move(b, mv, opp);
    }

    void play_turn(long long my_time, long long opp_time){
        // Choose best move
        Move mv = choose_move();
        if(mv.isPass){
            cout << "MOVE -1 -1 -1 -1" << endl;
            cout.flush();
            return;
        }
        // Output in 1-based indexing
        cout << "MOVE " << (mv.x1+1) << ' ' << (mv.y1+1) << ' ' << (mv.x2+1) << ' ' << (mv.y2+1) << endl;
        cout.flush();
        // Update our board with our own move
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
            agent.reset(); // ensure initial position
            agent.handle_ready(role);
        } else if(cmd=="TURN"){
            long long myt, oppt; cin>>myt>>oppt;
            agent.play_turn(myt, oppt);
        } else if(cmd=="OPP"){
            int x1,y1,x2,y2; long long t; cin>>x1>>y1>>x2>>y2>>t;
            agent.apply_opp_line(x1,y1,x2,y2);
            // No output
        } else if(cmd=="FINISH"){
            // Graceful exit
            // Optionally read trailing tokens, but spec says just end.
            break;
        } else {
            // Unknown line; consume rest of line to avoid desync
            string rest; getline(cin, rest);
        }
    }
    return 0;
}
