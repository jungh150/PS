#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    vector<int> b(n);
    int tmp = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a[i] = x + tmp;
        b[i] = x - tmp;
        tmp += k;
    }

    vector<int> armin(n); // a에서 오른쪽 원소들의 최솟값
    vector<int> brmax(n); // b에서 오른쪽 원소들의 최댓값

    int mint = 2e9;
    for (int i = n - 1; i >= 0; i--) {
        armin[i] = mint;
        mint = min(mint, a[i]);
    }

    int maxt = -2e9;
    for (int i = n - 1; i >= 0; i--) {
        brmax[i] = maxt;
        maxt = max(maxt, b[i]);
    }

    int ans = -2e9;
    
    for (int i = 0; i < n - 1; i++) {
        ans = max(ans, a[i] - armin[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        ans = max(ans, brmax[i] - b[i]);
    }

    cout << ans << '\n';
}