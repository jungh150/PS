#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a(n + 1);
    vector<int> s(n + 1);
    a[0] = s[0] = 0;
    for (int i = 1; i < n + 1; i++) {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }

    int m;
    cin >> m;

    while (m--) {
        int i, j;
        cin >> i >> j;
        cout << s[j] - s[i - 1] << '\n';
    }
}