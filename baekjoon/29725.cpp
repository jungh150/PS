#include <iostream>
#include <map>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    map<char, int> m;
    m['.'] = 0;
    m['K'] = 0;
    m['P'] = 1;
    m['N'] = 3;
    m['B'] = 3;
    m['R'] = 5;
    m['Q'] = 9;
    m['k'] = 0;
    m['p'] = -1;
    m['n'] = -3;
    m['b'] = -3;
    m['r'] = -5;
    m['q'] = -9;

    int ans = 0;
    for (int i = 0; i < 8; i++) {
        string s;
        cin >> s;
        for (char c: s) ans += m[c];
    }

    cout << ans << '\n';
}