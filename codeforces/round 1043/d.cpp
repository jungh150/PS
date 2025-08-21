#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
    long long k;
    cin >> k;

    vector<long long> cnt(16);
    long long tmp = 1;
    cnt[0] = 0;
    for (int i = 1; i < 16; i++) {
        cnt[i] = i * 9 * tmp;
        tmp *= 10;
    }

    long long ans = 0;
    for (int i = 15; i > 0; i--) {
        if (cnt[i] <= k) {
            k -= cnt[i];

        }
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