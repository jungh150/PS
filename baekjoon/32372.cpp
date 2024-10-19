#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    
    int sx = 1;
    int ex = n;
    int sy = 1;
    int ey = n;

    while (m--) {
        int x, y, k;
        cin >> x >> y >> k;

        if (k == 1) {
            ex = min(ex, x - 1);
            sy = ey = y;
        } else if (k == 2) {
            ex = min(ex, x - 1);
            sy = max(sy, y + 1);
        } else if (k == 3) {
            sx = ex = x;
            sy = max(sy, y + 1);
        } else if (k == 4) {
            sx = max(sx, x + 1);
            sy = max(sy, y + 1);
        } else if (k == 5) {
            sx = max(sx, x + 1);
            sy = ey = y;
        } else if (k == 6) {
            sx = max(sx, x + 1);
            ey = min(ey, y - 1);
        } else if (k == 7) {
            sx = ex = x;
            ey = min(ey, y - 1);
        } else if (k == 8) {
            ex = min(ex, x - 1);
            ey = min(ey, y - 1);
        }
    }

    cout << sx << ' ' << sy << '\n';
}