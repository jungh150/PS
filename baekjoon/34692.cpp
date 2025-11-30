#include <iostream>
#include <queue>
using namespace std;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    priority_queue<int, vector<int>, greater<>> pq;
    for (int i = 0; i < m; i++) pq.push(0);
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        t += pq.top();
        pq.pop();
        pq.push(t);
    }

    if (pq.top() <= k) cout << "WAIT\n";
    else cout << "GO\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}