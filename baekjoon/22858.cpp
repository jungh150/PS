#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> a[i];

    vector<int> d(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> d[i];

    vector<int> b(n + 1);
    for (int i = 0; i < k; i++) {
        for (int i = 1; i < n + 1; i++) {
            b[d[i]] = a[i];
        }
        swap(a, b);
    }

    for (int i = 1; i < n + 1; i++) cout << a[i] << ' ';
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