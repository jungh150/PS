#include <iostream>
#include <vector>
using namespace std;

void solve(int n, int w) {
    int maxv = 0;
    vector<int> num(n);
    for (int i = 0; i < n; i++) {
        cin >> num[i];
        maxv = max(maxv, num[i]);
    }

    int k = maxv / w + 1;
    vector<int> a(k, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            if (w * j <= num[i] && num[i] < w * (j + 1)) {
                a[j]++;
                break;
            }
        }
    }

    int cnt = 0;
    vector<int> b;

    int maxh = 0;
    int maxi = 0;

    for (int i = 0; i < k; i++) {
        if (a[i] > 0) {
            cnt++;
            b.push_back(a[i]);
        }
        if (a[i] > maxh) {
            maxh = a[i];
            maxi = i;
        }
    }

    double ans = 0.01;
    double unit = (double) 1 / maxh;
    for (int i = 0; i < k; i++) {
        ans += a[i] * ((double) (k - 1 - i) / (k - 1)) * unit;
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cout << fixed;
    cout.precision(8);

    int n, w;
    while (cin >> n >> w) {
        if (n == 0 && w == 0) break;
        solve(n, w);
    }
}