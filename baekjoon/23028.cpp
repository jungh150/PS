#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, a, b;
    cin >> n >> a >> b;
    b -= a;

    for (int i = 1; i < 11; i++) {
        int x, y;
        cin >> x >> y;

        if (n + i > 8) continue;

        int cnt = 0;
        while (a < 66 && cnt < x) {
            a += 3;
            cnt++;
        }
        b += 3 * min(6 - cnt, b);
    }

    if (a >= 66 && (a + b) >= 130) cout << "Nice\n";
    else cout << "Nae ga wae\n";
}