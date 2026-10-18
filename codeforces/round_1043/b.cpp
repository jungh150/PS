#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
    long long n;
    cin >> n;

    vector<long long> ans;

    long long tmp = 10;
    for (int i = 1; i < 20; i++) {
        if (n % (tmp + 1) == 0) ans.push_back(n / (tmp + 1));
        tmp *= 10;
    }

    if (ans.empty()) {
        cout << 0 << '\n';
    } else {
        cout << ans.size() << '\n';
        sort(ans.begin(), ans.end());
        for (long long x: ans) cout << x << ' ';
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}