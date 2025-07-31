#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> parent;

int find(int a) {
    if (parent[a] == a) return a;
    else return parent[a] = find(parent[a]);
}

bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        parent[b] = a;
        return true;
    } else {
        return false;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        parent = vector<int>(10000);
        for (int i = 0; i < 10000; i++) parent[i] = i;

        vector<vector<int>> edge(n, vector<int>(4));

        for (int i = 0; i < n; i++) {
            int a, b;
            cin >> a >> b;
            edge[i][0] = b - a;
            edge[i][1] = a;
            edge[i][2] = b;
            edge[i][3] = i + 1;
        }

        sort(edge.begin(), edge.end(), greater<>());

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            int a = edge[i][1];
            int b = edge[i][2];
            int idx = edge[i][3];
            if (unite(a, b)) {
                ans.push_back(idx);
            }
        }

        cout << ans.size() << '\n';
        for (int x: ans) cout << x << ' ';
        cout << '\n';
    }
}