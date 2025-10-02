#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    int num = 2000001;
    vector<bool> p(num, 1);
    p[0] = p[1] = 0;

    int sqnum = sqrt(num);
    for (int i = 2; i <= sqnum; i++) {
        if (p[i]) {
            for (int j = i * i; j < num; j += i) p[j] = 0;
        }
    }

    for (int i = 1; i <= 2000000; i++) {
        if (p[i]) continue;
        bool psb = true;
        for (int j = 0; j < n; j++) {
            if (i + j * m > 2000000 || p[i + j * m]) {
                psb = false;
                break;
            }
        }
        if (psb) {
            for (int j = 0; j < n; j++) {
                cout << i + j * m << ' ';
            }
            cout << '\n';
            return;
        }
    }

    cout << -1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}