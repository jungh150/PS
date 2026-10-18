#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<vector<vector<int>>> cnt(n + 1, vector<vector<int>>(n + 1, vector<int>(250, 0)));
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            for (int k = 1; k < 250; k++) cnt[i][j][k] = cnt[i - 1][j][k] + cnt[i][j - 1][k] - cnt[i - 1][j - 1][k];
            int x;
            cin >> x;
            cnt[i][j][x]++;
        }
    }

    long long ans = 0;
    for (int r2 = 1; r2 < n + 1; r2++) {
        for (int c2 = 1; c2 < n + 1; c2++) {
            for (int r1 = 1; r1 <= r2; r1++) {
                for (int c1 = 1; c1 <= c2; c1++) {
                    vector<int> tmp = cnt[r2][c2];
                    for (int k = 1; k < 250; k++) {
                        tmp[k] = tmp[k] - cnt[r2][c1 - 1][k] - cnt[r1 - 1][c2][k] + cnt[r1 - 1][c1 - 1][k];
                    }

                    bool psb = true;
                    int x = (r2 - r1 + 1) * (c2 - c1 + 1);

                    for (int k = 1; k <= x; k++) {
                        if (tmp[k] != 1) {
                            psb = false;
                            break;
                        }
                    }
                    for (int k = x + 1; k < 250; k++) {
                        if (tmp[k] != 0) {
                            psb = false;
                            break;
                        }
                    }

                    if (psb) ans++;
                }
            }
        }
    }

    cout << ans << '\n';
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