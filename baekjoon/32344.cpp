#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int r, c, n;
    cin >> r >> c >> n;

    vector<pair<int, int>> x(n + 1, {1e6, 0});
    vector<pair<int, int>> y(n + 1, {1e6, 0});
    for (int i = 0; i < n; i++) {
        int k, v, h;
        cin >> k >> v >> h;
        x[k].first = min(x[k].first, v);
        x[k].second = max(x[k].second, v);
        y[k].first = min(y[k].first, h);
        y[k].second = max(y[k].second, h);
    }

    long long maxv = 0;
    int maxi = 0;
    for (int i = 1; i < n + 1; i++) {
        long long w = max(0, x[i].second - x[i].first + 1);
        long long h = max(0, y[i].second - y[i].first + 1);
        long long tmp = w * h;
        if (tmp > maxv) {
            maxv = tmp;
            maxi = i;
        }
    }

    cout << maxi << ' ' << maxv << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}