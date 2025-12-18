#include <iostream>
#include <set>
using namespace std;

set<long long> ans;

void f(int cnt, long long val) {
    if (cnt == 1) {
        ans.insert(val);
        return;
    }
    f(cnt - 1, val * 2);
    if ((val - 1) % 3 == 0) {
        long long pre = (val - 1) / 3;
        if (pre > 1 && pre % 2 == 1) f(cnt - 1, pre);
    }
}

void solve() {
    int n;
    cin >> n;

    f(n, 1);

    cout << ans.size() << '\n';
    for (long long x: ans) cout << x << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}