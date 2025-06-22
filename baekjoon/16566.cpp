#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> parent;

int find(int a) {
    if (parent[a] == a) return a;
    else return parent[a] = find(parent[a]);
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) parent[a] = b;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> blue(m);
    for (int i = 0; i < m; i++) cin >> blue[i];
    sort(blue.begin(), blue.end());

    parent = vector<int>(m);
    for (int i = 0; i < m; i++) parent[i] = i;

    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        int tidx = upper_bound(blue.begin(), blue.end(), x) - blue.begin();
        int chosen = find(tidx);
        cout << blue[chosen] << '\n';
        if (chosen + 1 < m) unite(chosen, chosen + 1);
    }
}