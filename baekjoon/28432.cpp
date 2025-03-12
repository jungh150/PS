#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<string> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    char s = '.';
    char e = '.';
    set<string> stset;

    for (int i = 0; i < n; i++) {
        if (a[i] == "?") {
            if (i - 1 >= 0) s = a[i - 1][a[i - 1].size() - 1];
            if (i + 1 < n) e = a[i + 1][0];
        } else {
            stset.insert(a[i]);
        }
    }

    int m;
    cin >> m;

    while (m--) {
        string ans;
        cin >> ans;

        if (s != '.' && s != ans[0]) continue;
        if (e != '.' && e != ans[ans.size() - 1]) continue;
        if (stset.find(ans) != stset.end()) continue;

        cout << ans << '\n';
    }
}