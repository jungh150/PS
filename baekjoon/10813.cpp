#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);
    for (int i = 1; i < n + 1; i++) a[i] = i;

    while (m--) {
        int i, j;
        cin >> i >> j;
        swap(a[i], a[j]);
    }

    for (int i = 1; i < n + 1; i++) cout << a[i] << ' ';
    cout << '\n';
}