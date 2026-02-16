#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, char>> arr(m);
    for (int i = 0; i < m; i++) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        arr[i] = {b, a, c};
    }

    sort(arr.begin(), arr.end());

    for (int i = 0; i < m; i++) cout << get<2>(arr[i]);
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