#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

int n, m, k;
vector<int> c;
vector<vector<int>> e;
vector<int> parent;
vector<unordered_map<int, int>> setsize;
vector<long long> ans;

int find(int a) {
    if (parent[a] == a) return a;
    else return parent[a] = find(parent[a]);
}

bool unite(int w, int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;

    // 작은 쪽(b)에서 큰 쪽(a)으로 합치기 (small to large)
    if (setsize[a].size() < setsize[b].size()) swap(a, b);
    parent[b] = a;

    for (auto [cp, v]: setsize[b]) {
        if (setsize[a].count(cp)) {
            ans[cp] += (long long) w * setsize[a][cp] * v;
        }
        setsize[a][cp] += setsize[b][cp]; // a에 회사 cp에 속하는 창고가 없어도 해주어야 함
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k >> m;

    parent = vector<int>(n + 1);
    setsize = vector<unordered_map<int, int>>(n + 1);
    for (int i = 0; i < n + 1; i++) parent[i] = i;

    c = vector<int>(n + 1);
    for (int i = 1; i < n + 1; i++) {
        cin >> c[i];
        setsize[i][c[i]] = 1;
    }

    e = vector<vector<int>>(m, vector<int>(3));
    for (int i = 0; i < m; i++) {
        cin >> e[i][1] >> e[i][2] >> e[i][0];
    }

    sort(e.begin(), e.end(), greater<>());

    ans = vector<long long>(k + 1, 0);

    int cnt = 0;
    for (int i = 0; i < m; i++) {
        if (unite(e[i][0], e[i][1], e[i][2])) cnt++;
        if (cnt >= n - 1) break;
    }

    for (int i = 1; i < k + 1; i++) {
        cout << ans[i] << '\n';
    }
}