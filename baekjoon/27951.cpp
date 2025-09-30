#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    vector<int> cnt(4, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }

    int u, d;
    cin >> u >> d;

    if (cnt[1] + cnt[3] < u || cnt[2] + cnt[3] < d) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        int tmp = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == 1) {
                cout << "U";
            } else if (a[i] == 2) {
                cout << "D";
            } else {
                if (tmp < u - cnt[1]) {
                    cout << "U";
                    tmp++;
                } else {
                    cout << "D";
                }
            }
        }
        cout << '\n';
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