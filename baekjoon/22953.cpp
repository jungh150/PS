#include <iostream>
#include <vector>
using namespace std;

int n, k, c;
vector<int> a;
long long ans = 1e15;

long long mint() {
    long long l = 0;
    long long r = 1e15;
    while (l < r) {
        long long m = (l + r) / 2;
        long long tmp = 0;
        for (int i = 0; i < n; i++) {
            tmp += (m / a[i]);
        }
        if (tmp >= k) r = m;
        else l = m + 1;
    }
    return l;
}

void bt(int cnt) {
    if (cnt == c) {
        ans = min(ans, mint());
        return;
    }

    bool psb = false;
    for (int i = 0; i < n; i++) {
        if (a[i] > 1) {
            a[i]--;
            bt(cnt + 1);
            a[i]++;
            psb = true;
        }
    }

    if (!psb) {
        ans = min(ans, mint());
        return;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k >> c;

    a = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    bt(0);

    cout << ans << '\n';
}