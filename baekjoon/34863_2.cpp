#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n, l;
    cin >> n >> l;

    int tcnt = l;

    for (int i = 1; i < n + 1; i++) {
        int b;
        cin >> b;
    }

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
    int bigcntl = 0;
    int bigcntr = 0;

    for (int i = 1; i < k; i++) {
        if (w[i] > tcnt) {
            big.push_back(i);
            bigcntl += w[i];
        }
    }

    for (int i = k + 1; i < n + 1; i++) {
        if (w[i] > tcnt) {
            big.push_back(i);
            bigcntr += w[i];
        }
    }

    if (w[k] <= tcnt) {
        if (p + w[k] > l) {
            cout << "NO\n";
            return;
        }

        int s = 0;
        int e = l - (bigcntl + bigcntr) - w[k];
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
        int s = bigcntl;
        int e = l - w[k] - bigcntr;

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