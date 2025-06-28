#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<string> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<string> b = a;

    sort(b.begin(), b.end());
    bool flag = true;
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            flag = false;
            break;
        }
    }
    if (flag) {
        cout << "INCREASING\n";
        return 0;
    }

    sort(b.begin(), b.end(), greater<>());
    flag = true;
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            flag = false;
            break;
        }
    }
    if (flag) {
        cout << "DECREASING\n";
        return 0;
    }

    cout << "NEITHER\n";
}