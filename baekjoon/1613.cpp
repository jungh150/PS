#include <iostream>
#include <vector>
using namespace std;

int INTMAX = 1e8;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    vector<vector<int>> dst(n + 1, vector<int>(n + 1, INTMAX));

    for (int i = 0; i < k; i++) {
        int s, e;
        cin >> s >> e;
        dst[s][e] = 1;
    }
    
    for (int k = 1; k < n + 1; k++) {
        for (int i = 1; i < n + 1; i++) {
            for (int j = 1; j < n + 1; j++) {
                dst[i][j] = min(dst[i][j], dst[i][k] + dst[k][j]);
            }
        }
    }

    int s;
    cin >> s;

    while (s--) {
        int a, b;
        cin >> a >> b;
        if (dst[a][b] < INTMAX) cout << -1 << '\n';
        else if (dst[b][a] < INTMAX) cout << 1 << '\n';
        else cout << 0 << '\n';
    }
}