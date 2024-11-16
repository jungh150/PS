#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int a[100];
    int b[100];

    int n, m;
    cin >> n >> m;

    int idx = 0;
    for (int i = 0; i < n; i++) {
        int l, v;
        cin >> l >> v;
        for (int j = 0; j < l; j++) {
            a[idx++] = v;
        }
    }

    idx = 0;
    for (int i = 0; i < m; i++) {
        int l, v;
        cin >> l >> v;
        for (int j = 0; j < l; j++) {
            b[idx++] = v;
        }
    }

    int maxt = 0;
    for (int i = 0; i < 100; i++) {
        if (b[i] - a[i] > maxt) maxt = b[i] - a[i];
    }

    cout << maxt << '\n';
}