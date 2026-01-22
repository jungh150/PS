#include <iostream>
#include <queue>
using namespace std;

void solve() {
    int n;
    cin >> n;

    priority_queue<int> q;
    while (n--) {
        int a;
        cin >> a;

        if (a == 0) {
            if (q.empty()) {
                cout << -1 << '\n';
            } else {
                cout << q.top() << '\n';
                q.pop();
            }
        } else {
            for (int i = 0; i < a; i++) {
                int x;
                cin >> x;
                q.push(x);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}