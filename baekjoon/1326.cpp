#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> s(n + 1);
    vector<int> v(n + 1, false);

    for (int i = 1; i < n + 1; i++) {
        cin >> s[i];
    }

    int a, b;
    cin >> a >> b;

    int ans = INT_MAX;
    queue<pair<int, int>> q;
    q.emplace(a, 0);
    v[a] = true;
    while (!q.empty()) {
        auto [ts, tc] = q.front();
        q.pop();
        int unit = s[ts];

        int idx = ts - unit;
        while (idx > 0) {
            if (!v[idx]) {
                if (idx == b) {
                    ans = min(ans, tc + 1);
                    break;
                }
                q.emplace(idx, tc + 1);
                v[idx] = true;
            }
            idx -= unit;
        }

        idx = ts + unit;
        while (idx < n + 1) {
            if (!v[idx]) {
                if (idx == b) {
                    ans = min(ans, tc + 1);
                    break;
                }
                q.emplace(idx, tc + 1);
                v[idx] = true;
            }
            idx += unit;
        }
    }

    if (ans == INT_MAX) ans = -1;

    cout << ans << '\n';
}