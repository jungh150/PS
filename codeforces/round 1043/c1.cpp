#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<long long> num;
vector<long long> cost;

void solve() {
    long long n;
    cin >> n;

    long long ans = 0;
    for (int i = 24; i >= 0; i--) {
        while (num[i] <= n) {
            ans += cost[i];
            n -= num[i];
        }
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    num = vector<long long>(25);
    cost = vector<long long>(25);
    long long tmp = 1;
    for (int i = 0; i < 25; i++) {
        num[i] = tmp;
        cost[i] = 3 * tmp + i * tmp / 3;
        tmp *= 3;
    }

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}