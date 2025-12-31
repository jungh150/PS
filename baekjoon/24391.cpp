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
    if (a != b) {
        parent[b] = a;
        return true;
    } else {
        return false;
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    parent = vector<int>(n + 1);
    for (int i = 1; i < n + 1; i++) parent[i] = i;

    while (m--) {
        int a, b;
        cin >> a >> b;
        unite(a, b);
    }

    int ans = 0;
    int pre, cur;
    cin >> pre;
    for (int i = 1; i < n; i++) {
        cin >> cur;
        if (find(pre) != find(cur)) ans++;
        pre = cur;
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}