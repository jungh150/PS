#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;
    s = s.substr(0, 5);

    int n;
    cin >> n;

    int ans = 0;
    while (n--) {
        string tmp;
        cin >> tmp;
        if (tmp.substr(0, 5) == s) ans++;
    }

    cout << ans << '\n';
}