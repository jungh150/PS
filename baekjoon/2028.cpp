#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        string s = to_string(n);
        int ns = s.size();

        int pn = n * n;
        string ps = to_string(pn);
        int nps = ps.size();

        if (ps.substr(nps - ns, ns) == s) cout << "YES\n";
        else cout << "NO\n";
    }
}