#include <iostream>
#include <vector>
using namespace std;

int n, m, x;
vector<vector<int>> g;
int MAX = 1000000000;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> x;
    g = vector<vector<int>>(n + 1, vector<int>(n + 1, MAX));

    for (int i = 0; i < n + 1; i++) {
        g[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        g[a][b] = t;
    }

    for (int k = 1; k < n + 1; k++) { // 경유지 k
        for (int i = 1; i < n + 1; i++) { // 출발 노드 i
            for (int j = 1; j < n + 1; j++) { // 도착 노드 j
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }

    int maxa = 0;
    for (int i = 1; i < n + 1; i++) {
        maxa = max(maxa, g[i][x] + g[x][i]);
    }
    cout << maxa << '\n';
}