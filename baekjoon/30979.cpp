#include <iostream>
using namespace std;

void solve() {
    int t, n;
    cin >> t >> n;
    
    int sumt = 0;
    for (int i = 0; i < n; i++) {
        int f;
        cin >> f;
        sumt += f;
    }
    
    if (sumt >= t) cout << "Padaeng_i Happy\n";
    else cout << "Padaeng_i Cry\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}