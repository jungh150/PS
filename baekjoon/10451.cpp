#include <iostream>
#include <vector>
#include <set>
using namespace std;

vector<int> a;
vector<bool> vst, fin;
int ans = 0;

void dfs(int cur) {
    vst[cur] = true;
    int nxt = a[cur];

    if (!vst[nxt]) {
        dfs(nxt);
    } else if (!fin[nxt]) {
        ans++;
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

    ans = 0;
    for (int i = 1; i < n + 1; i++) {
        if (!vst[i]) dfs(i);
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}