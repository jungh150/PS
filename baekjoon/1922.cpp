#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m, k;
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    parent = vector<int>(n + 1);
    for (int i = 0; i < n + 1; i++) parent[i] = i;

    e = vector<vector<int>>(m, vector<int>(3));
    for (int i = 0; i < m; i++) {
        cin >> e[i][1] >> e[i][2] >> e[i][0];
    }

    sort(e.begin(), e.end());

    long long ans = 0;

    int cnt = 0;
    for (int i = 0; i < m; i++) {
        if (unite(e[i][0], e[i][1], e[i][2])) {
            ans += e[i][0];
            cnt++;
        }
        if (cnt >= n - 1) break;
    }

    cout << ans << '\n';
}