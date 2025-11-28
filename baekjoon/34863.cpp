#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n, l;
    cin >> n >> l;

    int tcnt = l;

    vector<int> b(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> b[i];

    vector<int> w(n + 1);
    w[0] = 0;
    for (int i = 1; i < n + 1; i++) {
        cin >> w[i];
        tcnt -= w[i];
    }

    int k, p;
    cin >> k >> p;

    vector<int> big;
    big.push_back(0);
    int bigcnt = 0;
    for (int i = 1; i < n + 1; i++) {
        if (w[i] > tcnt && i != k) {
            big.push_back(i);
            bigcnt += w[i];
        }
    }

    if (w[k] <= tcnt) {
        if (p + w[k] > l) {
            cout << "NO\n";
            return;
        }

        int s = 0;
        int e = l - bigcnt - w[k];
        for (int i: big) {
            s += w[i];
            e += w[i];
            if (s <= p && p <= e) {
                cout << "YES\n";
                return;
            }
        }

        cout << "NO\n";
    } else {
        int s = 0;
        int e = l - w[k];
        for (int i: big) {
            if (i < k) s += w[i];
            else e -= w[i];
        }
        if (s <= p && p <= e) cout << "YES\n";
        else cout << "NO\n";
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