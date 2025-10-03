#include <iostream>
#include <vector>
using namespace std;

void solve() {
    long long n, p, h;
    cin >> n >> p >> h;

    vector<bool> isup;
    long long tmp = h;
    for (int i = n; i > 0; i--) {
        if (tmp > (1L << (i - 1))) {
            isup.push_back(true);
            tmp = (1L << i) - tmp + 1;
        } else {
            isup.push_back(false);
        }
    }

    tmp = p;
    for (int i = isup.size() - 1; i >= 0; i--) {
        if (tmp <= (1L << i)) { // left
            if (isup[i]) {
                tmp = (1L << i) - tmp + 1;
                cout << 'L';
            } else {
                cout << 'R';
            }
        } else { // right
            if (isup[i]) {
                tmp = (1L << i) - (tmp - (1L << i)) + 1;
                cout << 'R';
            } else {
                tmp = tmp - (1L << i);
                cout << 'L';
            }
        }
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}