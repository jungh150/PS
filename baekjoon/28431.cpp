#include <iostream>
#include <vector>
using namespace std;

void solve() {
    vector<int> cnt(10, 0);
    for (int i = 0; i < 5; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    for (int i = 0; i < 10; i++) {
        if (cnt[i] % 2 == 1) {
            cout << i << '\n';
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}