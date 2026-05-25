#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// MST -> MBST
// 역은 성립X

int n, m;
vector<vector<int>> e;
vector<int> parent;

int find(int a) {
    if (parent[a] == a) return a;
    else return parent[a] = find(parent[a]);
}

bool unite(int w, int a, int b) {
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
    cin >> n >> m;

    e = vector<vector<int>>(m, vector<int>(4));
    for (int i = 0; i < m; i++) {
        cin >> e[i][1] >> e[i][2] >> e[i][0];
        e[i][3] = i + 1;
    }

    parent = vector<int>(n + 1);
    for (int i = 0; i < n + 1; i++) parent[i] = i;

    sort(e.begin(), e.end());

    long long ans1 = 0;
    int maxw = 0;
    int cnt1 = 0;
    bool fin = false;
    int idx = m - 1;
    for (int i = 0; i < m; i++) {
        if (unite(e[i][0], e[i][1], e[i][2])) {
            ans1 += e[i][0];
            cnt1++;
        }
        if (cnt1 >= n - 1) {
            if (!fin) {
                fin = true;
                maxw = e[i][0];
            }
            if (fin && e[i][0] > maxw) {
                idx = i - 1;
                break;
            }
        }
    }

    parent = vector<int>(n + 1);
    for (int i = 0; i < n + 1; i++) parent[i] = i;

    long long ans2 = 0;
    vector<int> res;
    int cnt2 = 0;
    for (int i = idx; i >= 0; i--) {
        if (unite(e[i][0], e[i][1], e[i][2])) {
            res.push_back(e[i][3]);
            ans2 += e[i][0];
            cnt2++;
        }
        if (cnt2 >= n - 1) break;
    }

    cout << "NO\n"; // MST이면서 MBST가 아닌 것은 항상 NO
    if (cnt2 == n - 1 && ans2 > ans1) {
        cout << "YES\n";
        for (int x: res) cout << x << '\n';
    } else {
        cout << "NO\n";
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