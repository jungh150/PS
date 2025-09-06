#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<long long> arr;
vector<int> parent;
map<int, vector<int>> group;

int find(long long a) {
    if (parent[a] == a) return a;
    else return parent[a] = find(parent[a]);
}

bool unite(long long a, long long b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (a > b) swap(a, b); // now, a < b
    parent[b] = a;
    for (long long x: group[b]) group[a].push_back(x);
    group.erase(b);
    return true;
}

void solve() {
    cin >> n;
    m = 2 * n;

    arr = vector<long long>(m);
    for (int i = 0; i < m; i++) cin >> arr[i];

    group = map<int, vector<int>>();
    for (int i = 0; i < m; i++) group[i] = {i};

    parent = vector<int>(m);
    for (int i = 0; i < m; i++) parent[i] = i;

    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            long long tmp = arr[i] ^ arr[j];
            for (int k = 0; k <= 20; k++) {
                if (tmp == (1 << k)) {
                    unite(i, j);
                    break;
                }
            }
        }
    }

    vector<int> idx;
    vector<int> cnt;
    idx.push_back(-1);
    cnt.push_back(-1);
    for (int i = 0; i < m; i++) {
        if (find(i) == i) {
            idx.push_back(i);
            cnt.push_back(group[i].size());
        }
    }

    // dp[i][j]: i번째 그룹까지 확인했을 때, 정확히 j개를 만들 수 있는지 여부
    int sz = cnt.size() - 1;
    vector<vector<bool>> dp(sz + 1, vector<bool>(n + 1, 0));
    dp[0][0] = 1;

    for (int i = 1; i < sz + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            if (j - cnt[i] >= 0 && dp[i - 1][j - cnt[i]]) dp[i][j] = 1;
            if (dp[i - 1][j]) dp[i][j] = 1;
        }
    }

    if (!dp[sz][n]) {
        cout << -1 << '\n';
        return;
    }

    // 역추적
    int cur = n;
    vector<int> gidx1;
    vector<int> gidx2;
    for (int i = sz; i >= 1; i--) {
        if (cur - cnt[i] >= 0 && dp[i - 1][cur - cnt[i]]) {
            gidx1.push_back(idx[i]);
            cur -= cnt[i];
        } else if (dp[i - 1][cur]) {
            gidx2.push_back(idx[i]);
        }
    }

    for (int idxt: gidx1) {
        for (int x: group[idxt]) cout << arr[x] << ' ';
    }
    cout << '\n';

    for (int idxt: gidx2) {
        for (int x: group[idxt]) cout << arr[x] << ' ';
    }
    cout << '\n';
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