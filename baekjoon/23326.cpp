#include <iostream>
#include <set>
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;

    set<int> s;

    for (int i = 1; i < n + 1; i++) {
        int x;
        cin >> x;
        if (x == 1) s.insert(i);
    }

    int cur = 1;
    while (q--) {
        int a, b;
        cin >> a;
        
        if (a == 1) {
            cin >> b;
            if (s.count(b)) s.erase(b);
            else s.insert(b);
        } else if (a == 2) {
            cin >> b;
            cur = (cur + b - 1) % n + 1;
        } else if (a == 3) {
            if (s.empty()) {
                cout << -1 << '\n';
            } else {
                auto it = s.lower_bound(cur);
                if (it == s.end()) cout << *s.begin() + n - cur << '\n'; // 뒤에 없으면 돌아와야 함
                else cout << *it - cur << '\n';
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}