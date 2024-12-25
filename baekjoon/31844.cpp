#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;

    bool psb = false;
    int num = 1;
    int cnt = 0;

    for (char c: s) {
        if (num == 2 || num == 3) cnt++;
        if (c == '.') continue;
        if (c == '#' && num == 2) psb = true;
        num++;
    }

    if (psb) cout << cnt - 1 << '\n';
    else cout << -1 << '\n';
}