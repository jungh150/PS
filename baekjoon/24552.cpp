#include <iostream>
using namespace std;

void solve() {
    string s;
    cin >> s;
    int n = s.size();

    int cur = 0;
    int pre = 0;
    int idxmi = -1;
    int idxze = -1;

    for (int i = 0; i < n; i++) {
        if (s[i] == '(') cur = pre + 1;
        else if (s[i] == ')') cur = pre - 1;

        if (cur == 0) idxze = i;
        if (cur == -1 && idxmi == -1) idxmi = i;

        pre = cur;
    }

    if (idxmi != -1) { // 중간에 -1 있으면
        int cnt = 0;
        for (int i = 0; i <= idxmi; i++) {
            if (s[i] == ')') cnt++;
        }
        cout << cnt << '\n';
    } else if (pre != 0) { // 마지막이 0이 아니면
        int cnt = 0;
        if (idxze == -1) idxze = 0;
        for (int i = idxze; i < n; i++) {
            if (s[i] == '(') cnt++;
        }
        cout << cnt << '\n';
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