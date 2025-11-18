#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n); // 0: 사람, 1: 햄버거, -1: 먹은 햄버거
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == 'H') a[i] = 1;
        else if (c == 'P') a[i] = 0;
    }

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] != 0) continue;
        // 사람이면
        for (int j = max(0, i - k); j <= min(n - 1, i + k); j++) {
            if (a[j] == 1) {
                a[j] = -1;
                cnt++;
                break;
            }
        }
    }

    cout << cnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}