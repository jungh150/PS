#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s, t;
    while (cin >> s >> t) {
        int sn = s.size();
        int tn = t.size();
        int si = 0;
        int ti = 0;
        while (si < sn && ti < tn) {
            if (s[si] == t[ti]) si++;
            ti++;
        }
        if (si == sn) cout << "Yes\n";
        else cout << "No\n";
    }
}