#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    string s;
    cin >> n >> s;

    // pi 배열 (실패 함수) 채우기
    vector<int> pi(n, 0);
    int j = 0;
    for (int i = 1; i < n; i++) {
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) pi[i] = ++j;
    }

    cout << n - pi[n - 1] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}