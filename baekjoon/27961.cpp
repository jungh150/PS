#include <iostream>
#include <map>
using namespace std;

void solve() {
    long long n;
    cin >> n;

    map<long long, int> m;
    for (int i = 0; i < 50; i++) {
        m[1LL << i] = i + 1;
    }

    if (n == 0) cout << 0 << '\n';
    else cout << m.lower_bound(n)->second << '\n';
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