#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    string s;
    cin >> s;

    while (m--) {
        string p;
        cin >> p;
        int idx = 0;
        bool psb = true;
        for (int i = 0; i < n; i++) {
            while (idx < p.size() && s[i] != p[idx]) idx++;
            if (idx >= p.size()) {
                psb = false;
                break;
            }
            idx++;
        }
        if (psb) cout << "true\n";
        else cout << "false\n";
    }
}