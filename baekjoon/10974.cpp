#include <iostream>
#include <vector>
using namespace std;

int n;
vector<bool> chk;

void func(int cnt, string res) {
    if (cnt == 0) {
        cout << res << '\n';
        return;
    }
    for (int i = 1; i < n + 1; i++) {
        if (chk[i]) continue;
        chk[i] = true;
        res += to_string(i);
        res += ' ';
        func(cnt - 1, res);
        chk[i] = false;
        res.pop_back();
        res.pop_back();
    }
}

void solve() {
    cin >> n;
    chk = vector<bool>(n + 1, false);
    func(n, "");
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}