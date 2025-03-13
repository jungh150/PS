#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<int> a;
vector<int> ans;

void dfs(int pre, int idx) {
    if (idx == m) {
        for (int x: ans) cout << x << ' ';
        cout << '\n';
    } else {
        for (int i = pre; i < n; i++) {
            ans.push_back(a[i]);
            dfs(i, idx + 1);
            ans.pop_back();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    a = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    dfs(0, 0);
}