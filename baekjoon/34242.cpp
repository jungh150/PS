#include <iostream>
#include <vector>
using namespace std;

void solve() {
    string s;
    cin >> s;
    int n = s.size();

    int score = 0;
    for (int i = 0; i < n - 2; i++) {
        if (s.substr(i, 3) == "+^+") score++;
        else if (s.substr(i, 3) == "-^-") score--;
    }

    int ans = score;
    for (int i = 0; i < n; i++) {
        int tmp = score;

        // 기존 점수 빼기
        if (i - 2 >= 0) {
            if (s.substr(i - 2, 3) == "+^+") tmp--;
            else if (s.substr(i - 2, 3) == "-^-") tmp++;
        }
        if (i - 1 >= 0 && i + 1 < n) {
            if (s.substr(i - 1, 3) == "+^+") tmp--;
            else if (s.substr(i - 1, 3) == "-^-") tmp++;
        }
        if (i + 2 < n) {
            if (s.substr(i, 3) == "+^+") tmp--;
            else if (s.substr(i, 3) == "-^-") tmp++;
        }

        // 새로운 점수 더하기
        if (i - 2 >= 0 && i + 1 < n) {
            if (s.substr(i - 2, 2) + s[i + 1] == "+^+") tmp++;
            else if (s.substr(i - 2, 2) + s[i + 1] == "-^-") tmp--;
        }
        if (i - 1 >= 0 && i + 2 < n) {
            if (s[i - 1] + s.substr(i + 1, 2) == "+^+") tmp++;
            else if (s[i - 1] + s.substr(i + 1, 2) == "-^-") tmp--;
        }

        ans = max(ans, tmp);
    }

    cout << ans << '\n';
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