#include <iostream>
#include <vector>
using namespace std;

int n, m, ans;
vector<int> a;

void dfs(int cur, int idx, int cnt) {
    if (idx == n || cnt == m) {
        ans = max(ans, cur);
        return;
    }
    dfs(cur + a[idx + 1], idx + 1, cnt + 1);
    dfs(cur / 2 + a[idx + 2], idx + 2, cnt + 1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    a = vector<int>(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> a[i];

    dfs(1, 0, 0);

    cout << ans << '\n';
}