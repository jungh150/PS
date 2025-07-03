#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t, n, m;
    cin >> t;

    cin >> n;
    vector<int> a(n + 1);
    vector<int> dpa(n + 1);
    dpa[0] = 0;
    for (int i = 1; i < n + 1; i++) {
        cin >> a[i];
        dpa[i] = dpa[i - 1] + a[i];
    }

    cin >> m;
    vector<int> b(m + 1);
    vector<int> dpb(m + 1);
    dpb[0] = 0;
    for (int i = 1; i < m + 1; i++) {
        cin >> b[i];
        dpb[i] = dpb[i - 1] + b[i];
    }

    map<int, int> ma;
    for (int i = 1; i < n + 1; i++) {
        for (int j = 0; j < i; j++) {
            int sumt = dpa[i] - dpa[j];
            if (ma.count(sumt) == 1) ma[sumt]++;
            else ma[sumt] = 1;
        }
    }

    map<int, int> mb;
    for (int i = 1; i < m + 1; i++) {
        for (int j = 0; j < i; j++) {
            int sumt = dpb[i] - dpb[j];
            if (mb.count(sumt) == 1) mb[sumt]++;
            else mb[sumt] = 1;
        }
    }

    long long ans = 0;
    for (auto it = ma.begin(); it != ma.end(); it++) {
        int target = t - it->first;
        if (mb.count(target)) ans += ((long long) (it->second) * (mb[target]));
    }
    cout << ans << '\n';
}