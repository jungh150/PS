#include <iostream>
using namespace std;

void solve() {
    int n;
    cin >> n;

    while (n--) {
        string s;
        cin >> s;

        if (s == "yonsei") {
            cout << "Yonsei Won!" << '\n';
            return;
        } else if (s == "korea") {
            cout << "Yonsei Lost..." << '\n';
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}