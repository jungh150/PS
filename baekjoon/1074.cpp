#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int cnt = 0;
int ans = 0;
int r, c;

void search(int sx, int sy, int size) {
    if (size == 1) {
        if (r == sy && c == sx) {
            ans = cnt;
        }
        cnt++;
        return;
    }
    int div = size / 2;

    if (r < sy + div) {
        if (c < sx + div) {
            search(sx, sy, div);
        } else {
            cnt += div * div;
            search(sx + div, sy, div);
        }
    } else {
        if (c < sx + div) {
            cnt += 2 * div * div;
            search(sx, sy + div, div);
        } else {
            cnt += 3 * div * div;
            search(sx + div, sy + div, div);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n >> r >> c;

    int msize = pow(2, n);
    search(0, 0, msize);

    cout << ans << '\n';
}