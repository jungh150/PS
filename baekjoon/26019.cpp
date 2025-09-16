#include <iostream>
#include <vector>
using namespace std;

long long MAX_VAL = 1e18;

void solve () {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a[i].push_back(x);
    }

    vector<vector<long long>> dp(n, vector<long long>(n + 1, MAX_VAL)); // total cost
    for (int i = 0; i < n; i++) {

    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}