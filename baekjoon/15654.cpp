#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<int> a;
vector<int> ans;
vector<bool> chk;

void dfs(int idx) {
    if (idx == m) {
        for (int x: ans) cout << x << ' ';
        cout << '\n';
        return;
    }
    for (int i = 0; i < n; i++) {
        if (chk[i]) continue;
        chk[i] = true;
        ans[idx] = a[i];
        dfs(idx + 1);
        chk[i] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    a = vector<int>(n);
    ans = vector<int>(m);
    chk = vector<bool>(n, false);

    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());

    dfs(0);
}