#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> ans;
vector<bool> chk;

void dfs(int idx) {
    if (idx == m) {
        for (int x: ans) cout << x << ' ';
        cout << '\n';
        return;
    }
    for (int i = 1; i < n + 1; i++) {
        if (!chk[i]) {
            chk[i] = true;
            ans[idx] = i;
            dfs(idx + 1);
            chk[i] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    ans = vector<int>(m);
    chk = vector<bool>(n + 1);

    dfs(0);
}