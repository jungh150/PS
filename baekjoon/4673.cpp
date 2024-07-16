#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    bool sn[10001];
    fill_n(sn, 10001, true);

    for (int i = 1; i < 10001; i++) {
        int tmp = i;
        int ans = tmp;
        while (tmp > 0) {
            ans += tmp % 10;
            tmp = tmp / 10;
        }
        if (ans < 10001) sn[ans] = false;
    }

    for (int i = 1; i < 10001; i++) {
        if (sn[i]) cout << i << '\n';
    }
}