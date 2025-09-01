#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int k;
    cin >> k;
    string b;
    cin >> b;

    vector<int> keya;
    vector<bool> keyb;

    int tmpa = 0;
    bool bomb = false;
    bool finJ = false;
    bool existJ = false;

    for (int i = 0; i < k; i++) {
        if (b[i] == 'A') {
            tmpa++;
        } else if (b[i] == 'D') {
            bomb = true;
        } else if (b[i] == 'J') {
            keya.push_back(tmpa);
            keyb.push_back(bomb);
            tmpa = 0;
            bomb = false;
            existJ = true;
            if (i == k - 1) finJ = true;
        }
        if (i == k - 1) {
            keya.push_back(tmpa);
            keyb.push_back(bomb);
        }
    }

    if (!existJ) {
        cout << "NO\n";
    }

    int kn = keya.size();
    if (finJ) {
        keya[kn - 1] += keya[0];
        if (!keyb[kn - 1]) keyb[kn - 1] = keyb[0];
    }

    int idx = 0;
    int si = 0;
    if (finJ) si = 1;
    bool flag = true;

    for (int i = 0; i < n; i++) {
        if (a[i] == -1) {
            if (!keyb[idx]) {
                cout << "NO\n";
                return 0;
            }
        } else if (a[i] >= 1) {
            if (keya[idx] < a[i]) {
                cout << "NO\n";
                return 0;
            }
        }
        idx++;
        if (idx == kn) idx = si;
    }

    cout << "YES\n";
}