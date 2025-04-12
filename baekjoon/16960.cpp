#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> sw(n + 1);

    for (int i = 1; i < n + 1; i++) {
        int x;
        cin >> x;

        for (int j = 0; j < x; j++) {
            int k;
            cin >> k;
            sw[i].push_back(k);
        }
    }

    for (int i = 1; i < n + 1; i++) {
        vector<bool> l(m + 1, 0);

        for (int j = 1; j < n + 1; j++) {
            if (j == i) continue;
            for (int k: sw[j]) l[k] = 1;
        }

        bool psb = 1;
        for (int j = 1; j < m + 1; j++) {
            if (!l[j]) psb = 0;
        }

        if (psb) {
            cout << 1 << '\n';
            return 0;
        }
    }

    cout << 0 << '\n';
}