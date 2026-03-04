#include <iostream>
using namespace std;

void solve() {
    long long n;
    cin >> n;

    if (n * n <= 1e8) cout << "Accepted\n";
    else cout << "Time limit exceeded\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}