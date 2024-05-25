#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<bool> p = vector<bool>(4, true);

    for (int i = 0; i < 2; i++) {
        int x;
        cin >> x;
        p[x] = false;
    }

    int cnt = 0;
    int ans;

    for (int i = 1; i < 4; i++) {
        if (p[i]) {
            cnt++;
            ans = i;
        }
    }

    if (cnt == 1) {
        cout << ans << '\n';
    }
    else {
        cout << -1 << '\n';
    }

}