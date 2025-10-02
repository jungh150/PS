#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i + 1;
    }

    sort(a.begin(), a.end(), greater<>());

    long long ans = 0;
    long long ansmax = 0;
    long long ansmin = 0;

    long long curmax = a[0].first;
    long long curmin = a[0].first;
    long long cursum = 0;

    for (int i = 0; i < n; i++) {
        curmin = a[i].first;
        cursum += a[i].first;
        long long tmp = curmax + curmin + cursum;
        if (tmp > ans) {
            ans = tmp;
            ansmin = i;
        }
    }

    cout << ansmin + 1 << '\n';
    for (int i = ansmax; i <= ansmin; i++) cout << a[i].second << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}