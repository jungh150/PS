#include <iostream>
#include <vector>
#include <set>
using namespace std;

int n, m, as;
set<int> s;
vector<int> a;
vector<int> ans;

void dfs(int idx) {
    if (idx == m) {
        for (int x: ans) cout << x << ' ';
        cout << '\n';
        return;
    }
    for (int i = 0; i < as; i++) {
        if (idx > 0 && a[i] < ans[idx - 1]) continue;
        ans[idx] = a[i];
        dfs(idx + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    ans = vector<int>(m);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        s.insert(x);
    }
    a = vector<int>(s.begin(), s.end());
    as = a.size();

    dfs(0);
}