#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    vector<bool> a(n, false);
    vector<bool> b(n, false);

    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        b[x] = true;
    }

    while (k--) {
        swap(a, b);
        for (int i = 0; i < n; i++) {
            int pre = i - 1;
            int nxt = i + 1;
            if (i == 0) pre = n - 1;
            if (i == n - 1) nxt = 0;
            
            if (a[pre] && a[nxt]) b[i] = false;
            else if (a[pre] || a[nxt]) b[i] = true;
            else b[i] = false;
        }
    }

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (b[i]) cnt++;
    }

    cout << cnt << '\n';
}