#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<long long> arr;
vector<long long> parent;
vector<long long> gsize;

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
    gsize[a] += gsize[b];
    return true;
}

void solve() {
    cin >> n;
    m = 2 * n;

    arr = vector<long long>(m);
    for (int i = 0; i < m; i++) cin >> arr[i];

    parent = vector<long long>(m);
    gsize = vector<long long>(m, 1);
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

    vector<long long> cnt;
    for (int i = 0; i < m; i++) {
        if (find(i) == i) cnt.push_back(gsize[i]);
    }

    // 냅색 후 역추적
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