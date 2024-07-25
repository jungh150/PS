#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<int> ans;
vector<int> chk;

void dfs(int idx) {
    if (idx == m) {
        for (int x: ans) cout << x << ' ';
        cout << '\n';
        return;
    }
    for (int i = 1; i < 10001; i++) {
        if (chk[i] > 0) {
            chk[i]--;
            ans[idx] = i;
            dfs(idx + 1);
            chk[i]++;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    ans = vector<int>(m);
    chk = vector<int>(10001, 0);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        chk[x]++;
    }

    dfs(0);
}