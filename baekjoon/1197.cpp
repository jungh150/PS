#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> parent;

int find(int a) {
    if (parent[a] == a) return a;
    else return parent[a] = find(parent[a]);
}

bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    parent[b] = a;
    return true;
}

void solve() {
    int v, e;
    cin >> v >> e;

    parent = vector<int>(v + 1);
    for (int i = 0; i < v + 1; i++) parent[i] = i;
    
    vector<vector<int>> edge;
    for (int i = 0; i < e; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edge.push_back({c, a, b});
    }

    sort(edge.begin(), edge.end());

    int ans = 0;
    int cnt = 0;
    for (auto x: edge) {
        if (unite(x[1], x[2])) {
            ans += x[0];
            cnt++;
        }
        if (cnt >= v - 1) break;
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}