#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
int parent[100001];
vector<vector<int>> edge;

int find(int a) {
    if (parent[a] == a) {
        return a;
    } else {
        parent[a] = find(parent[a]);
        return parent[a];
    }
}

void unionf(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) parent[b] = a;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    edge = vector<vector<int>>(m, vector<int>(3));

	for (int i = 1; i <= n; i++) {
		parent[i] = i;
	}

    for (int i = 0; i < m; i++) {
        cin >> edge[i][1] >> edge[i][2] >> edge[i][0];
    }

    sort(edge.begin(), edge.end());

    int ans = 0;
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        if (cnt == n - 2) break;
        if (find(edge[i][1]) != find(edge[i][2])) {
            unionf(edge[i][1], edge[i][2]);
            ans += edge[i][0];
            cnt++;
        }
    }

    cout << ans << '\n';
}