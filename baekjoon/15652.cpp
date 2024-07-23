#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> ans;

void dfs(int idx) {
    if (idx == m) {
        for (int x: ans) cout << x << ' ';
        cout << '\n';
        return;
    }
    int s = 1;
    if (idx > 0) s = ans[idx - 1];
    for (int i = s; i < n + 1; i++) {
        ans[idx] = i;
        dfs(idx + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    ans = vector<int>(m);

    dfs(0);
}