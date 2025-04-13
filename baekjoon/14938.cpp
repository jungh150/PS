#include <iostream>
#include <vector>
using namespace std;

int MAX_SIZE = 1000000000;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, r;
    cin >> n >> m >> r;

    vector<int> item(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> item[i];

    vector<vector<int>> g(n + 1, vector<int>(n + 1, MAX_SIZE));
    for (int i = 1; i < n + 1; i++) g[i][i] = 0;
    for (int i = 0; i < r; i++) {
        int a, b, l;
        cin >> a >> b >> l;
        g[a][b] = l;
        g[b][a] = l;
    }

    for (int k = 1; k < n + 1; k++) { // 경유지
        for (int i = 1; i < n + 1; i++) { // 출발지
            for (int j = 1; j < n + 1; j++) { // 도착지
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i < n + 1; i++) { // 예은이가 떨어진 지역
        int tmp = 0;
        for (int j = 1; j < n + 1; j++) { // 각 지역별로 아이템을 먹을 수 있는지 탐색
            if (g[i][j] <= m) tmp += item[j];
        }
        ans = max(ans, tmp);
    }

    cout << ans << '\n';
}