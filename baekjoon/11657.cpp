#include <iostream>
#include <vector>
using namespace std;

long long INTMAX = 1e12;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> edge;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edge.push_back({a, b, c});
    }

    vector<long long> dst(n + 1, INTMAX);
    dst[1] = 0;

    bool nc = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int a = edge[j][0];
            int b = edge[j][1];
            int c = edge[j][2];
            if (dst[a] == INTMAX) continue;
            if (dst[a] + c < dst[b]) {
                dst[b] = dst[a] + c;
                if (i == n - 1) nc = true; // s로부터 도달할 수 있는 음의 사이클
            }
        }
    }

    if (nc) {
        cout << -1 << '\n';
        return 0;
    }

    for (int i = 2; i < n + 1; i++) {
        if (dst[i] == INTMAX) cout << -1 << '\n';
        else cout << dst[i] << '\n';
    }
}