#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;
    
    vector<vector<int>> gem(n, vector<int>(2));
    for (int i = 0; i < n; i++) {
        int m, v;
        cin >> m >> v;
        gem[i][0] = v;
        gem[i][1] = m;
    }

    vector<int> bag(k);
    for (int i = 0; i < k; i++) cin >> bag[i];

    sort(gem.begin(), gem.end(), greater<>());
    sort(bag.begin(), bag.end());

    long long ans = 0;
    vector<bool> chk(k, 0);

    for (int i = 0; i < n; i++) {
        int l = 0;
        int r = k;
        while (l < r) {
            int m = (l + r) / 2;
            if (bag[m] < gem[i][1]) {
                l = m + 1;
            } else {
                r = m;
            }
        }

        int tmp = l;
        while (chk[tmp]) tmp++;

        if (tmp < k) {
            ans += gem[i][0];
            chk[tmp] = 1;
        }
    }

    cout << ans << '\n';
}