#include <iostream>
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
    
    // 1000 곱하기 (10은 반올림을 위해서)
    if (ph == 0 && pg == 0) ans = 50 * 1000;
    else ans = 1000 * 100 * ph / (ph + pg);

    // 반올림 처리
    if (ans % 10 >= 5) ans = ans / 10 + 1;
    else ans = ans / 10;

    // 100의 몫과 나머지로 출력
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