#include <iostream>
#include <vector>
using namespace std;

int n, m;
int ans = 0;
vector<vector<bool>> combi;
vector<bool> chk;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    chk = vector<bool>(n + 1, 0);
    combi = vector<vector<bool>>(n + 1, vector<bool>(n + 1, 0));

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        combi[a][b] = 1;
        combi[b][a] = 1;
    }

    for (int i = 1; i < n + 1; i++) {
        for (int j = i + 1; j < n + 1; j++) {
            for (int k = j + 1; k < n + 1; k++) {
                if (!combi[i][j] && !combi[j][k] && !combi[k][i]) ans++;
            }
        }
    }

    cout << ans << '\n';
}