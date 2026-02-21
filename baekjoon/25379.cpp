#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x % 2 == 0) a[i] = 0;
        else a[i] = 1;
    }

    // 0을 왼쪽으로 몰기
    long long cnt = 0;
    long long ans1 = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) cnt++;
        else ans1 += cnt;
    }

    // 1을 왼쪽으로 몰기
    cnt = 0;
    long long ans2 = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == 1) cnt++;
        else ans2 += cnt;
    }

    cout << min(ans1, ans2) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}