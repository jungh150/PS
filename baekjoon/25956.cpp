#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> ans(n, 0);
    stack<pair<int, int>> s; // 레벨, 인덱스
    for (int i = 0; i < n; i++) {
        if (s.empty() || s.top().first == a[i] || s.top().first == a[i] - 1) {
            s.emplace(a[i], i);
        } else {
            while (!s.empty() && s.top().first != a[i]) {
                int val = s.top().first;
                int cnt = 1;
                s.pop();
                while (!s.empty() && s.top().first == val) {
                    cnt++;
                    s.pop();
                }
                if (!s.empty() && s.top().first == val - 1) {
                    ans[s.top().second] = cnt;
                } else {
                    cout << -1 << '\n';
                    return;
                }
            }
            s.emplace(a[i], i);
        }
    }

    while (!s.empty() && s.top().first != 1) {
        int val = s.top().first;
        int cnt = 1;
        s.pop();
        while (!s.empty() && s.top().first == val) {
            cnt++;
            s.pop();
        }
        if (!s.empty() && s.top().first == val - 1) {
            ans[s.top().second] = cnt;
        } else {
            cout << -1 << '\n';
            return;
        }
    }

    for (int x: ans) cout << x << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}