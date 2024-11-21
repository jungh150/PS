#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int INTMAX = 1000000000;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long a, b;
    cin >> a >> b;

    queue<pair<long long, int>> q;
    q.emplace(a, 0);
    int ans = -1;

    while (!q.empty()) {
        long long x = q.front().first;
        int cnt = q.front().second;
        q.pop();
        if (x == b) {
            ans = cnt;
            break;
        } else if (x < b) {
            q.emplace(x * 2, cnt + 1);
            q.emplace(10 * x + 1, cnt + 1);
        }
    }

    if (ans == -1) cout << -1 << '\n';
    else cout << ans + 1 << '\n';
}