#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n, l;
    cin >> n >> l;

    vector<int> w(n);
    vector<int> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];
    for (int i = 0; i < n; i++) cin >> w[i];

    long long wsum = 0;
    long long wxsum = 0;
    for (int i = 0; i < n; i++) {
        wsum += w[i];
        wxsum += ((long long) w[i] * x[i]);
    }

    cout << fixed;
    cout.precision(10);
    cout << (double) wxsum / wsum << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}