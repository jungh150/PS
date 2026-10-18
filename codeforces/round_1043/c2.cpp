#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<long long> num;
vector<long long> cost;

void solve() {
    long long n, k;
    cin >> n >> k;

    if (k >= n) {
        cout << 3 * n << '\n';
        return;
    }

    long long ans = 0; // 원래 비용
    vector<long long> cnt(25); // 거래 종류 별 사용 횟수
    long long tcnt = 0; // 총 거래 횟수
    for (int i = 24; i >= 0; i--) {
        while (num[i] <= n) {
            ans += cost[i];
            n -= num[i];
            cnt[i]++;
            tcnt++;
        }
    }
    
    if (k < tcnt) {
        cout << -1 << '\n';
        return;
    } else if (k == tcnt) {
        cout << ans << '\n';
        return;
    }

    k = k - tcnt; // 여유분
    for (int i = 24; i >= 0; i--) { // 현재 거래
        if (cnt[i] == 0) continue;
        for (int j = i - 1; j >= 0; j--) {
        //for (int j = 0; j < i; j++) { // 치환하려는 거래
            long long cur = min(cnt[i], k / (num[i - j] - 1)); // 치환 가능한 개수
            k -= (num[i - j] - 1) * cur;
            ans += (cost[j] * num[i - j] - cost[i]) * cur;
            cnt[i] -= cur;
            cnt[j] += num[i - j] * cur;
            if (cnt[i] == 0) break;
            if (k == 0) break;
        }
        if (k == 0) break;
    }

    cout << ans << '\n';
    // cout << "-------------\n";

    // // 개수
    // long long sumt = 0;
    // for (int i = 0; i < 25; i++) sumt += cnt[i];
    // cout << sumt << '\n';
    // // 비용
    // long long sumc = 0;
    // for (int i = 0; i < 25; i++) sumc += cost[i] * cnt[i];
    // cout << sumc << '\n';
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

    // for (long long x: num) cout << x << ' ';
    // cout << '\n';
    // for (long long x: cost) cout << x << ' ';
    // cout << '\n';
    // for (int i = 0; i < 25; i++) cout << (double) cost[i] / num[i] << ' ';
    // cout << '\n';

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}