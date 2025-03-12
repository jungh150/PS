#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    while (1) {
        int n, p;
        cin >> n;

        if (n == 0) break;
        
        cin >> p;

        int tmp = p;
        if (p > n / 2) tmp = n - p + 1;
        if (tmp % 2 == 0) tmp--;

        int ans[4];
        ans[0] = tmp;
        ans[1] = tmp + 1;
        ans[2] = n - tmp;
        ans[3] = n - tmp + 1;

        for (int x: ans) {
            if (x != p) cout << x << ' ';
        }
        cout << '\n';
    }
}