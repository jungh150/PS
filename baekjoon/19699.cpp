#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

bool p[10000];
int n, m;
vector<int> h;
vector<bool> chk;
set<int> ans;

void dfs(int idx, int res) {
    if (idx == m) {
        if (res < 10000 && p[res]) ans.insert(res);
        return;
    }
    for (int i = 0; i < n; i++) {
        if (!chk[i]) {
            chk[i] = 1;
            dfs(idx + 1, res + h[i]);
            chk[i] = 0;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    fill_n(p, 10000, 1);
    p[0] = p[1] = 0;

    for (int i = 2; i < 5000; i++) {
        int tmp = i * 2;
        while (tmp < 10000) {
            p[tmp] = 0;
            tmp += i;
        }
    }

    cin >> n >> m;
    h = vector<int>(n);
    chk = vector<bool>(n, false);
    for (int i = 0; i < n; i++) cin >> h[i];
    sort(h.begin(), h.end());

    dfs(0, 0);
    if (ans.empty()) {
        cout << -1 << '\n';
    } else {
        for (int x: ans) cout << x << ' ';
        cout << '\n';
    }
}