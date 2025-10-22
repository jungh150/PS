#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> x(n + 1, 0);
    vector<int> y(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int a, b, p, q;
        cin >> a >> b >> p >> q;
        x[a] += p;
        y[a] += q;
        x[b] += q;
        y[b] += p;
    }

    long long minv = 1e15;
    long long maxv = 0;
    for (int i = 1; i < n + 1; i++) {
        long long tmp = 0;
        if (x[i] != 0 || y[i] != 0) tmp = (long long) x[i] * x[i] * 1000 / (x[i] * x[i] + y[i] * y[i]);
        minv = min(minv, tmp);
        maxv = max(maxv, tmp);
    }
    
    cout << maxv << '\n' << minv << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}