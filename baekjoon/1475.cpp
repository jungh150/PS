#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;

    vector<int> cnt(10, 0);
    for (int c: s) {
        if (c == '9') cnt[6]++;
        else cnt[c - '0']++;
    }

    int ans = 0;
    for (int i = 0; i < 10; i++) {
        if (i == 6) ans = max(ans, (cnt[6] + 1) / 2);
        else ans = max(ans, cnt[i]);
    }

    cout << ans << '\n';
}