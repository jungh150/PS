#include <iostream>
#include <vector>
using namespace std;

void solve() {
    string t, p;
    getline(cin, t);
    getline(cin, p);

    int n = t.size();
    int m = p.size();

    // pi 배열 (실패 함수) 채우기
    vector<int> pi(m, 0);
    int j = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && p[i] != p[j]) j = pi[j - 1];
        if (p[i] == p[j]) pi[i] = ++j;
    }

    // kmp
    vector<int> ans;
    j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && t[i] != p[j]) j = pi[j - 1];
        if (t[i] == p[j]) {
            if (j == m - 1) {
                ans.push_back(i - m + 2); // 매칭 성공
                j = pi[j];
            } else {
                j++;
            }
        }
    }

    cout << ans.size() << '\n';
    for (int x: ans) cout << x << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}