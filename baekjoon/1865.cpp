#include <iostream>
#include <vector>
using namespace std;

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
        vector<int> dst(n + 1, 100000000);

        int s, e, t;
        dst[1] = 0;

        for (int i = 0; i < m; i++) {
            cin >> s >> e >> t;
            edge.push_back({s, e, t});
            edge.push_back({e, s, t});
        }

        for (int i = 0; i < w; i++) {
            cin >> s >> e >> t;
            edge.push_back({s, e, -t});
        }

        int es = edge.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < es; j++) {
                s = edge[j][0];
                e = edge[j][1];
                t = edge[j][2];
                if (dst[e] > dst[s] + t) {
                    dst[e] = dst[s] + t;
                }
            }
        }

        bool infinite = false;
        for (int i = 0; i < es; i++) {
	    	s = edge[i][0];
	    	e = edge[i][1];
	    	t = edge[i][2];
	    	if (dst[e] > dst[s] + t) {
	    		infinite = true;
                break;
	    	}
	    }

        if (infinite) cout << "YES\n";
        else cout << "NO\n";
    }
}