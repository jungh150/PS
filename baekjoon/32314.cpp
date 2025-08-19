#include <iostream>
using namespace std;

void solve() {
    int n;
    cin >> n;

    int cnt = 0;
    while (n--) {
        int d;
        cin >> d;
        if (d % 2 == 1) cnt++;
    }
    
    cout << cnt << '\n';
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