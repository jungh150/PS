#include <iostream>
using namespace std;

void solve() {
    int n, x;
    cin >> n >> x;

    long long sumt = 0;
    for (int i = 0; i < n; i++) {
        int score;
        cin >> score;
        sumt += score;
    }

    long long a = n * x - sumt;
    long long b = 100 - x;

    cout << max(0LL, (a + b - 1) / b) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}