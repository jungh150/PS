// Reference: green55 teamnote
// https://github.com/green5555/Teamnote/blob/master/TeamNote/MCMF.cpp

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

//O(VEf), Average = O(Ef)
const int MAX=2010;
struct MinCostMaxFlow{
    struct edg{ int pos, cap, rev; ll cost; };
    vector<edg> adj[MAX];
    void clear(){
        for(int i=0; i<MAX; i++) adj[i].clear();
    }
    void add_edge(int from, int to, int cap, int cost){
        adj[from].push_back({to, cap, (int)adj[to].size(), cost});
        adj[to].push_back({from, 0, (int)adj[from].size()-1, -cost});
    }
    ll dist[MAX];
    int pa[MAX], pe[MAX];
    bool inque[MAX];
    bool spfa(int src, int sink){
        memset(dist, 0x3f, sizeof(dist));
        memset(inque, 0, sizeof(inque));
        queue<int> que;
        dist[src] = 0;
        inque[src] = 1;
        que.push(src);
        bool ok = 0;
        while(!que.empty()){
            int x = que.front();
            que.pop();
            if(x == sink) ok = 1;
            inque[x] = 0;
            for(int i=0; i<adj[x].size(); i++){
                edg e = adj[x][i];
                if(e.cap > 0 && dist[e.pos] > dist[x] + e.cost){
                    dist[e.pos] = dist[x] + e.cost;
                    pa[e.pos] = x;
                    pe[e.pos] = i;
                    if(!inque[e.pos]){
                        inque[e.pos] = 1;
                        que.push(e.pos);
                    }
                }
            }
        }
        return ok;
    }
    pll match(int src, int sink){
        ll min_cost=0, max_flow=0;
        while(spfa(src, sink)){
            int cap = 1e9;
            for(int pos = sink; pos != src; pos = pa[pos]){
                cap = min(cap, adj[pa[pos]][pe[pos]].cap);
            }
            min_cost += dist[sink] * cap;
            max_flow += cap;
            for(int pos = sink; pos != src; pos = pa[pos]){
                int rev = adj[pa[pos]][pe[pos]].rev;
                adj[pa[pos]][pe[pos]].cap -= cap;
                adj[pos][rev].cap += cap;
            }
        }
        return {min_cost, max_flow};
    }
};

void solve(int v, int e) {
    MinCostMaxFlow mcmf;

    mcmf.add_edge(2 * 1, 2 * 1 + 1, 2, 0); // 1의 in -> 1의 out
    mcmf.add_edge(2 * v, 2 * v + 1, 2, 0); // v의 in -> v의 out
    for (int i = 2; i < v; i++) {
        mcmf.add_edge(2 * i, 2 * i + 1, 1, 0); // 각 정점마다 in -> out
    }

    for (int i = 0; i < e; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        mcmf.add_edge(2 * a + 1, 2 * b, 1, c); // a의 out -> b의 in
    }

    cout << mcmf.match(1 * 2, v * 2 + 1).first << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int v, e;
    while (cin >> v >> e) {
        solve(v, e);
    }
}