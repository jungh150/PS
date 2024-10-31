#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    int sums = 0;
    int maxs = 0;
    bool isfin = false;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;

        if (b > n) {
            sums += (b - n);
            if (b > maxs) maxs = b;
        }
    }

    sums -= (maxs - n);
    cout << sums << '\n';
}