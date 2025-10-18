#include <iostream>
#include <vector>
using namespace std;

vector<int> g;
vector<long long> gp;
vector<long long> gs;

int find(int a) {
    if (g[a] == a) return a;
    else return g[a] = find(g[a]);
}

long long unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b) return gp[a];
    if (a > b) swap(a, b); // now, a < b

    long long newp = gp[a] + gp[b] + gs[a] * gs[b];
    long long news = gs[a] + gs[b];
    gp[a] = newp;
    gs[a] = news;
    g[b] = a;

    return gp[a];
}

void solve() {
    int n, q;
    cin >> n >> q;

    g = vector<int>(n + 1); // group number
    gp = vector<long long>(n + 1); // group power
    gs = vector<long long>(n + 1); // group sum

    for (int i = 1; i < n + 1; i++) {
        int x;
        cin >> x;
        g[i] = i;
        gp[i] = 0;
        gs[i] = x;
    }

    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << unite(a, b) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}