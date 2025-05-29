#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

int n, m;
vector<int> a;
vector<int> cura;
vector<tuple<int, int, int>> op;
map<vector<int>, int> vst;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    a = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    cin >> m;
    op = vector<tuple<int, int, int>>(m);
    for (int i = 0; i < m; i++) {
        int l, r, c;
        cin >> l >> r >> c;
        op[i] = {l, r, c};
    }

    priority_queue<pair<int, vector<int>>> q;
    q.push({0, a});
    vst[a] = 0;
    while (!q.empty()) {
        int curc = -q.top().first;
        cura = q.top().second;
        q.pop();

        for (int i = 0; i < m; i++) {
            auto [l, r, c] = op[i];
            swap(cura[l - 1], cura[r - 1]);
            if (!vst.count(cura) || curc + c < vst[cura]) {
                vst[cura] = curc + c;
                q.push({-(curc + c), cura});
            }
            swap(cura[l - 1], cura[r - 1]);
        }
    }

    sort(a.begin(), a.end());

    if (vst.count(a)) cout << vst[a] << '\n';
    else cout << -1 << '\n';
}