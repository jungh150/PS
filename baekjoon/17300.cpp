#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int l;
    cin >> l;

    vector<int> a(l);
    for (int i = 0; i < l; i++) cin >> a[i];

    if (l < 3 || l > 9) {
        cout << "NO\n";
        return;
    }

    vector<bool> used(10, 0);
    int pre = 0;

    for (int cur: a) {
        if (used[cur]) {
            cout << "NO\n";
            return;
        }
        
        if (cur == 1) {
            if (pre == 3) {
                if (!used[2]) {
                    cout << "NO\n";
                    return;
                }
            } else if (pre == 7) {
                if (!used[4]) {
                    cout << "NO\n";
                    return;
                }
            } else if (pre == 9) {
                if (!used[5]) {
                    cout << "NO\n";
                    return;
                }
            }
        } else if (cur == 2) {
            if (pre == 8) {
                if (!used[5]) {
                    cout << "NO\n";
                    return;
                }
            }
        } else if (cur == 3) {
            if (pre == 1) {
                if (!used[2]) {
                    cout << "NO\n";
                    return;
                }
            } else if (pre == 9) {
                if (!used[6]) {
                    cout << "NO\n";
                    return;
                }
            } else if (pre == 7) {
                if (!used[5]) {
                    cout << "NO\n";
                    return;
                }
            }
        } else if (cur == 4) {
            if (pre == 6) {
                if (!used[5]) {
                    cout << "NO\n";
                    return;
                }
            }
        } else if (cur == 6) {
            if (pre == 4) {
                if (!used[5]) {
                    cout << "NO\n";
                    return;
                }
            }
        } else if (cur == 7) {
            if (pre == 1) {
                if (!used[4]) {
                    cout << "NO\n";
                    return;
                }
            } else if (pre == 9) {
                if (!used[8]) {
                    cout << "NO\n";
                    return;
                }
            } else if (pre == 3) {
                if (!used[5]) {
                    cout << "NO\n";
                    return;
                }
            }
        } else if (cur == 8) {
            if (pre == 2) {
                if (!used[5]) {
                    cout << "NO\n";
                    return;
                }
            }
        } else if (cur == 9) {
            if (pre == 3) {
                if (!used[6]) {
                    cout << "NO\n";
                    return;
                }
            } else if (pre == 7) {
                if (!used[8]) {
                    cout << "NO\n";
                    return;
                }
            } else if (pre == 1) {
                if (!used[5]) {
                    cout << "NO\n";
                    return;
                }
            }
        }

        used[cur] = 1;
        pre = cur;
    }

    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}