#include <iostream>
#include <vector>
using namespace std;

int n;

void solve() {
    vector<string> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> cnt(26, 0);
    vector<vector<int>> rcnt(26, vector<int>(n, 0)); // row count
    vector<vector<int>> ccnt(26, vector<int>(n, 0)); // column count
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cnt[a[i][j] - 'A']++;
            rcnt[a[i][j] - 'A'][i]++;
            ccnt[a[i][j] - 'A'][j]++;
        }
    }

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < n; j++) {
            if (rcnt[i][j] > 1) {
                for (int k = 0; k < n; k++) {
                    if (ccnt[i][k] > 1) {
                        cout << j + 1 << ' ' << k + 1 << ' ';
                        break;
                    }
                }
            } else if (cnt[i] == 1 && rcnt[i][j] == 1) {
                for (int k = 0; k < n; k++) {
                    if (cnt[i] == 1 && ccnt[i][k] == 1) {
                        cout << j + 1 << ' ' << k + 1 << ' ';
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        if (cnt[i] == n - 1) {
            cout << char(i + 'A') << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    while (cin >> n) {
        solve();
    }
}