#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> b(m);
    for (int i = 0; i < m; i++) cin >> b[i];

    int ai = 0;
    int bi = 0;

    while (ai < n && bi < m) {
        if (a[ai] < b[bi]) {
            cout << a[ai] << ' ';
            ai++;
        } else {
            cout << b[bi] << ' ';
            bi++;
        }
    }

    while (ai < n) {
        cout << a[ai] << ' ';
        ai++;
    }

    while (bi < m) {
        cout << b[bi] << ' ';
        bi++;
    }

    cout << '\n';
}