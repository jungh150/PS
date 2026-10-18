#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int n;
vector<vector<int>> m;
vector<pair<int, int>> elice;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int djk(int si, int sj, int ei, int ej) {
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> q;
    vector<vector<int>> dst(n, vector<int>(n, INT_MAX));
    q.push({0, si, sj});
    dst[si][sj] = 0;

    while (!q.empty()) {
        int cost = q.top()[0];
        int curi = q.top()[1];
        int curj = q.top()[2];
        q.pop();

        if (curi == ei && curj == ej) {
            return cost;
        }

        for (int i = 0; i < 4; i++) {
            int nxti = curi + dx[i];
            int nxtj = curj + dy[i];
            if (nxti >= 0 && nxti < n && nxtj >= 0 && nxtj < n) {
                int next_cost = cost + m[curi][curj] + m[nxti][nxtj];
                if (next_cost < dst[nxti][nxtj]) {
                    dst[nxti][nxtj] = next_cost;
                    q.push({next_cost, nxti, nxtj});
                }
            }
        }
    }

    return INT_MAX;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    m = vector<vector<int>>(n, vector<int>(n));
    elice = vector<pair<int, int>>(5);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> m[i][j];
        }
    }

    for (int i = 0; i < 5; i++) {
        cin >> elice[i].first >> elice[i].second;
        elice[i].first--;
        elice[i].second--;
    }

    int ans = 0;
    ans += djk(0, 0, elice[0].first, elice[0].second);
    ans += djk(elice[0].first, elice[0].second, elice[1].first, elice[1].second);
    ans += djk(elice[1].first, elice[1].second, elice[2].first, elice[2].second);
    ans += djk(elice[2].first, elice[2].second, elice[3].first, elice[3].second);
    ans += djk(elice[3].first, elice[3].second, elice[4].first, elice[4].second);

    cout << ans << '\n';
}
