#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<tuple<int, int, int>> e;
vector<int> parent;

int find(int a) {
    if (parent[a] == a) return a;
    else return parent[a] = find(parent[a]);
}

bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        parent[a] = b;
        return true;
    } else {
        return false;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    
    vector<pair<int, int>> x;
    vector<pair<int, int>> y;
    vector<pair<int, int>> z;

    for (int i = 0; i < n; i++) {
        int tx, ty, tz;
        cin >> tx >> ty >> tz;
        x.emplace_back(tx, i);
        y.emplace_back(ty, i);
        z.emplace_back(tz, i);
    }

    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    sort(z.begin(), z.end());

    for (int i = 0; i < n - 1; i++) {
        int dst;
        dst = abs(x[i].first - x[i + 1].first);
        e.emplace_back(dst, x[i].second, x[i + 1].second);
        dst = abs(y[i].first - y[i + 1].first);
        e.emplace_back(dst, y[i].second, y[i + 1].second);
        dst = abs(z[i].first - z[i + 1].first);
        e.emplace_back(dst, z[i].second, z[i + 1].second);
    }
    
    sort(e.begin(), e.end());

    parent = vector<int>(n);
    for (int i = 0; i < n; i++) parent[i] = i;

    int cnt = 0;
    long long ans = 0;
    for (auto [w, i, j]: e) {
        if (unite(i, j)){
            cnt++;
            ans += w;
        }
        if (cnt == n - 1) break;
    }

    cout << ans << '\n';
}