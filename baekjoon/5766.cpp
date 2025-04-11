#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    while (1) {
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0) break;

        vector<int> a(10001, 0);
        int maxi1 = 0;
        int maxi2 = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int x;
                cin >> x;
                a[x]++;
            }
        }

        int first = 0;
        for (int i = 1; i < 10001; i++) {
            first = max(first, a[i]);
        }

        int second = 0;
        for (int i = 1; i < 10001; i++) {
            if (a[i] < first) second = max(second, a[i]);
        }

        vector<int> ans;
        for (int i = 1; i < 10001; i++) {
            if (a[i] == second) ans.push_back(i);
        }

        sort(ans.begin(), ans.end());

        for (int x: ans) cout << x << ' ';
        cout << '\n';
    }
}