#include <iostream>
#include <vector>
using namespace std;

bool a[80001];
int ps[80001];

void solve() {
    int n;
    cin >> n;
    cout << ps[n] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 1; i <= 80000; i++) {
        if (i % 3 == 0 || i % 7 == 0) a[i] = true;
    }

    a[0] = 0;
    for (int i = 1; i <= 80000; i++) {
        ps[i] = ps[i - 1];
        if (a[i]) ps[i] += i;
    }

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}