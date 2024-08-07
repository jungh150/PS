#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    int a1, a2, a3;
    long long an;
    cin >> a1 >> a2 >> a3;
    for (int i = 3; i < n; i++) cin >> an;
    if (n == 3) an = a3;

    int d = a2 - a1;
    if (a3 - a2 == d) {
        cout << an + d << '\n';
    } else {
        int r = a2 / a1;
        cout << an * r << '\n';
    }
}