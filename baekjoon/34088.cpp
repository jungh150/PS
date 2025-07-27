#include <iostream>
#include <random>
#include <chrono>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    if (n == 1) {
        cout << 1 << '\n';
        return 0;
    }

    int ans = 0;

    for (int k = 0; k < 30; k++) {
        int idx1 = rng() % n;
        int idx2 = rng() % n;
        while (idx1 == idx2) idx2 = rng() % n;

        cout << "a1=" << a[idx1] << ' ';
        cout << "a2=" << a[idx2] << ' ';

        int dif = abs(a[idx1] - a[idx2]);
        cout << "dif=" << dif << '\n';
        vector<pair<int, int>> div; // {약수, 나머지}
        for (int i = 1; i * i <= dif; i++) {
            if (dif % i == 0) {
                div.emplace_back(i, a[idx1] % i);
                if (i * i != n) div.emplace_back(dif / i, a[idx1] % (dif / i));
            }
        }

        for (auto [d, rem]: div) {
            if (d == 1) continue;
            int cnt = 0;
            for (int x: a) {
                if (x % d == rem) cnt++;
            }
            cout << "d=" << d << ' ';
            cout << "rem=" << rem << ' ';
            cout << "cnt=" << cnt << '\n';
            ans = max(ans, cnt);
        }
    }

    cout << ans << '\n';
}