#include <iostream>
#include <vector>
using namespace std;

void solve() {
    vector<bool> a(86400, false);

    int c, h;
    cin >> c >> h;
    
    string s;
    for (int i = 0; i < c + h; i++) {
        cin >> s;
        int hh = stoi(s.substr(0, 2));
        int mm = stoi(s.substr(3, 2));
        int ss = stoi(s.substr(6, 2));
        int time = hh * 60 * 60 + mm * 60 + ss;
        for (int i = time; i < min(86400, time + 40); i++) a[i] = true;
    }

    int cnt = 86400;
    for (bool up: a) {
        if (up) cnt--;
    }

    cout << cnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}