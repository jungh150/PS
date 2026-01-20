#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> cnt(4, 0);
    for (int i = 0; i < 3 * n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    for (int i = 1; i <= 3; i++) {
        if (cnt[i] < n) cout << i << '\n';
    }

    for (int i = 1; i <= 3; i++) {
        if (cnt[i] > n) cout << i << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}