#include <iostream>
#include <vector>
using namespace std;

int n, m, k;
vector<string> a;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> k;
    a = vector<string>(n);
    
    for (int i = 0; i < n; i++) cin >> a[i];

    int ansv = 0;
    vector<vector<char>> ans(k, vector<char>(k));

    int total = (n / k) * (m / k);

    for (int l = 0; l < k; l++) {
        for (int o = 0; o < k; o++) {
            vector<int> cnt(26, 0);
            for (int i = 0; i < n; i += k) {
                for (int j = 0; j < m; j += k) {
                    cnt[a[i + l][j + o] - 'A']++;
                }
            }
            int maxt = 0;
            int maxx = 0;
            for (int x = 0; x < 26; x++) {
                if (cnt[x] > maxt) {
                    maxt = cnt[x];
                    maxx = x;
                }
            }
            ans[l][o] = 'A' + maxx;
            ansv += total - maxt;
        }
    }

    cout << ansv << '\n';

    for (int i = 0; i < n; i += k) {
        for (int l = 0; l < k; l++) {
            for (int j = 0; j < m; j += k) {
                for (int o = 0; o < k; o++) {
                    cout << ans[l][o];
                }
            }
            cout << '\n';
        }
    }
}