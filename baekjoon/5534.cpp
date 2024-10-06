#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    string s;
    cin >> s;
    int ss = s.size();

    int ans = 0;
    for (int i = 0; i < n; i++) {
        string st;
        cin >> st;
        int sts = st.size();
        bool psb = false;
        for (int j = 0; j < sts; j++) {
            if (st[j] != s[0]) continue;
            int jmp = 1;
            int idx = 1;
            while (true) {
                if (j + idx * jmp < sts && st[j + idx * jmp] == s[idx]) {
                    idx++;
                    if (idx >= ss) {
                        psb = true;
                        break;
                    }
                } else {
                    jmp++;
                    idx = 1;
                    if (jmp >= sts) break;
                }
            }
            if (psb) break;
        }
        if (psb) ans++;
    }

    cout << ans << '\n';
}