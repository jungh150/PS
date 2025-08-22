#include <iostream>
using namespace std;

void solve() {
    string s;
    cin >> s;
    
    if (s.size() == 2) {
        cout << stoi(s.substr(0, 1)) + stoi(s.substr(1, 1)) << '\n';
    } else if (s.size() == 4) {
        cout << stoi(s.substr(0, 2)) + stoi(s.substr(2, 2)) << '\n';
    } else {
        if (s[1] == '0') cout << stoi(s.substr(0, 2)) + stoi(s.substr(2, 1)) << '\n';
        else cout << stoi(s.substr(0, 1)) + stoi(s.substr(1, 2)) << '\n';
    }
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