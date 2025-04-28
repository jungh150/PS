#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> music(n);
    for (int i = 0; i < n; i++) cin >> music[i];

    int m;
    cin >> m;

    vector<int> dream(m);
    for (int i = 0; i < m; i++) cin >> dream[i];

    vector<int> ans;
    for (int k = 1; k < m; k++) {
        for (int i = 0; i < m; i++) {
            int psb = true;
            int di = i;
            for (int j = 0; j < n; j++) {
                if (di >= m || music[j] != dream[di]) {
                    psb = false;
                    break;
                }
                di += k;
            }
            if (psb) {
                ans.push_back(k - 1);
                break;
            }
        }
    }

    if (ans.empty()) cout << -1 << '\n';
    else cout << ans[0] << ' ' << ans[ans.size() - 1] << '\n';
}