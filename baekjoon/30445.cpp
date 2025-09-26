#include <iostream>
#include <vector>
using namespace std;

void solve() {
    string s;
    getline(cin, s);
    
    long long ph = 0;
    long long pg = 0;

    for (char c: s) {
        if (c == 'H' || c == 'A' || c == 'P' || c == 'Y') ph++;
        if (c == 'S' || c == 'A' || c == 'D') pg++;
    }
    
    long long ans = 0;
    
    if (ph == 0 && pg == 0) ans = 50 * 100000;
    else ans = 100000 * 100 * ph / (ph + pg);

    ans = ans / 100;
    if (ans % 10 >= 5) ans = ans / 10 + 1;
    else ans = ans / 10;

    cout << ans / 100 << '.';
    long long rem = ans % 100;
    if (rem / 10 == 0) cout << 0 << rem << '\n';
    else cout << rem << '\n';
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