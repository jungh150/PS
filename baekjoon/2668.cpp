#include <iostream>
#include <vector>
#include <set>
using namespace std;

vector<int> a;
vector<bool> vst, fin;
set<int> ans;

void dfs(int cur) {
    vst[cur] = true;
    int nxt = a[cur];

    if (!vst[nxt]) {
        dfs(nxt);
    } else if (!fin[nxt]) {
        int x = cur;
        while (1) {
            ans.insert(x);
            x = a[x];
            if (x == cur) break;
        }
    }

    fin[cur] = true;
}

void solve() {
    int n;
    cin >> n;

    a = vector<int>(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> a[i];

    vst = vector<bool>(n + 1, false);
    fin = vector<bool>(n + 1, false);

    for (int i = 1; i < n + 1; i++) {
        if (!vst[i]) dfs(i);
    }

    cout << ans.size() << '\n';
    for (auto it = ans.begin(); it != ans.end(); it++) cout << *it << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}