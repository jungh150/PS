#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    if (n % 3 == 0) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < n; j++) {
                cout << ((i + j) % n) + 1 << ' ';
            }
        }
        cout << '\n';
    } else {
        vector<int> ans;
        for (int i = 1; i <= n; i++) {
            if (i % 2 == 1) ans.push_back(i);
        }
        for (int i = 1; i <= n; i++) {
            if (i % 2 == 0) ans.push_back(i);
        }

        for (int i = 0; i < 3; i++) {
            for (int x: ans) cout << x << ' ';
        }
        cout << '\n';
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