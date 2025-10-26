#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<bool> vst(n + 1, false);
    vector<vector<int>> e(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        e[a].push_back(b);
        e[b].push_back(a);
    }

    long long ans = 0;

    queue<pair<int, int>> q;
    q.emplace(1, 0);
    vst[1] = true;
    while (!q.empty()) {
        int cur = q.front().first;
        int cnt = q.front().second;
        q.pop();
        bool isleaf = true;
        for (int nxt: e[cur]) {
            if (!vst[nxt]) {
                isleaf = false;
                q.emplace(nxt, cnt + 1);
                vst[nxt] = true;
            }
        }
        if (isleaf) {
            if (cnt % 2 == 1) ans += 1;
        }
    }

    if (ans % 2 == 1) cout << "Yes\n";
    else cout << "No\n";
}