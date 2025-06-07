#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int x, y;
    cin >> x >> y;

    int xn = n * x / 100;
    int yn = 0;
    for (int k: a) {
        if (k >= y) yn++;
    }

    cout << xn << ' ' << yn << '\n';
}