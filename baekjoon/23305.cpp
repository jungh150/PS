#include <iostream>
#include <vector>
using namespace std;

int MAX_VAL = 1e6 + 1;

void solve() {
    int n;
    cin >> n;

    vector<int> a(MAX_VAL, 0);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a[x]++;
    }

    vector<int> b(MAX_VAL, 0);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        b[x]++;
    }

    int ans = 0;
    for (int i = 0; i < MAX_VAL; i++) {
        ans += abs(a[i] - b[i]);
    }

    cout << ans / 2 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}