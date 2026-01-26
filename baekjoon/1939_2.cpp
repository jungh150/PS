#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> parent;

int find(int a) {
    if (parent[a] == a) return a;
    else return find(parent[a]);
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    parent[b] = a;
}

void solve() {
    int n, m;
    cin >> n >> m;

    parent = vector<int>(n + 1);
    for (int i = 1; i < n + 1; i++) parent[i] = i;

    vector<vector<int>> edge(m);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edge[i] = {c, a, b};
    }

    sort(edge.begin(), edge.end(), greater<>());

    int s, e;
    cin >> s >> e;

    for (int i = 0; i < m; i++) {
        int a = edge[i][1];
        int b = edge[i][2];
        int c = edge[i][0];
        unite(a, b);
        if (find(s) == find(e)) {
            cout << c << '\n';
            break;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}