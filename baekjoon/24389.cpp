#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<bool> ori(32, false);
    vector<bool> ans(32, true);

    int idx = 31;
    while (n != 0) {
        if (n % 2 == 1) {
            ori[idx] = true;
            ans[idx] = false;
        }
        idx--;
        n /= 2;
    }

    for (int i = 31; i >= 0; i--) {
        if (!ans[i]) {
            ans[i] = true;
            break;
        } else {
            ans[i] = false;
        }
    }

    int cnt = 0;
    for (int i = 0; i < 32; i++) {
        if (ori[i] != ans[i]) cnt++;
    }

    cout << cnt << '\n';
}