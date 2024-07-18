#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>
using namespace std;

int n;
vector<vector<int>> m;
vector<vector<int>> dst;
vector<pair<int, int>> elice;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int djk(int si, int sj, int ei, int ej) {
    priority_queue<tuple<int, int, int>> q;
    q.emplace(0, si, sj);
    dst[si][sj] = 0;

    while (!q.empty()) {
        int cost = -get<0>(q.top());
        int curi = get<1>(q.top());
        int curj = get<2>(q.top());
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nxti = curi + dx[i];
            int nxtj = curj + dy[i];
            if (nxti > 0 && nxti <= n && nxtj > 0 && nxtj <= n) {
                dst[nxti][nxtj] = min(dst[nxti][nxtj], cost + m[curi][curj] * m[nxti][nxtj]);
            }
        }
    }

    return dst[ei][ej];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    m = vector<vector<int>>(n + 1, vector<int>(n + 1));
    elice = vector<pair<int, int>>(5);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> m[i][j];
        }
    }

    for (int i = 0; i < 5; i++) {
        cin >> elice[i].first >> elice[i].second;
    }

    int ans1 = 0;
    ans1 += djk(1, 1, elice[0].first, elice[0].second);
    ans1 += djk(elice[0].first, elice[0].second, elice[1].first, elice[1].second);
    ans1 += djk(elice[1].first, elice[1].second, elice[2].first, elice[2].second);
    ans1 += djk(elice[2].first, elice[2].second, elice[3].first, elice[3].second);
    ans1 += djk(elice[3].first, elice[3].second, elice[4].first, elice[4].second);

    int ans2 = 0;
    ans2 += djk(1, 1, elice[4].first, elice[4].second);
    ans2 += djk(elice[4].first, elice[4].second, elice[1].first, elice[1].second);
    ans2 += djk(elice[1].first, elice[1].second, elice[2].first, elice[2].second);
    ans2 += djk(elice[2].first, elice[2].second, elice[3].first, elice[3].second);
    ans2 += djk(elice[3].first, elice[3].second, elice[0].first, elice[0].second);

    cout << min(ans1, ans2) << '\n';
}