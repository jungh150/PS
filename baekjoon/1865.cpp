#include <iostream>
#include <vector>
using namespace std;

int INTMAX = 1e8;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tc;
    cin >> tc;

    while (tc--) {
        int n, m, w;
        cin >> n >> m >> w;

        vector<vector<int>> edge;

        for (int i = 0; i < m; i++) {
            int s, e, t;
            cin >> s >> e >> t;
            edge.push_back({s, e, t});
            edge.push_back({e, s, t});
        }

        for (int i = 0; i < w; i++) {
            int s, e, t;
            cin >> s >> e >> t;
            edge.push_back({s, e, -t});
        }

        vector<int> dst(n + 1, INTMAX);
        dst[1] = 0;

        int es = edge.size();

        bool nc = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < es; j++) {
                int s = edge[j][0];
                int e = edge[j][1];
                int c = edge[j][2];
                if (dst[s] + c < dst[e]) {
                    dst[e] = dst[s] + c;
                    if (i == n - 1) nc = true;
                }
            }
        }

        if (nc) cout << "YES\n";
        else cout << "NO\n";
    }
}