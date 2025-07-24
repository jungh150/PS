#include <iostream>
#include <vector>
using namespace std;

long long INTMAX = 1e15;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<long long>> dst(n + 1, vector<long long>(n + 1, INTMAX));
    for (int i = 0; i < m; i++) {
        long long a, b, c;
        cin >> a >> b >> c;
        dst[a][b] = min(dst[a][b], c);
    }

    for (int i = 1; i < n + 1; i++) {
        dst[i][i] = 0;
    }

    for (int k = 1; k < n + 1; k++) { // 경유지
        for (int i = 1; i < n + 1; i++) { // 출발 노드
            for (int j = 1; j < n + 1; j++) { // 도착 노드
                dst[i][j] = min(dst[i][j], dst[i][k] + dst[k][j]);
            }
        }
    }

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            if (dst[i][j] == INTMAX) cout << 0 << ' ';
            else cout << dst[i][j] << ' ';
        }
        cout << '\n';
    }
}