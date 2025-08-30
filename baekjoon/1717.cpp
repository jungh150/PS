#include <iostream>
#include <vector>
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
    int n, m;
    cin >> n >> m;

    parent = vector<int>(n + 1);
    for (int i = 0; i < n + 1; i++) parent[i] = i;

    while (m--) {
        int q, a, b;
        cin >> q >> a >> b;

        if (q == 0) {
            unite(a, b);
        } else if (q == 1) {
            if (find(a) == find(b)) cout << "YES\n";
            else cout << "NO\n";
        }
    }
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