#include <iostream>
#include <vector>
using namespace std;

int n, m, k;
vector<int> parent;
vector<int> fcnt;
vector<int> candy;

int find(int a) {
    if (parent[a] == a) return a;
    else return parent[a] = find(parent[a]);
}

void unite(int a, int b) {
    if (a > b) swap(a, b); // now a < b
    a = find(a);
    b = find(b);
    if (a != b) {
        parent[b] = a;
        fcnt[a] += fcnt[b];
        candy[a] += candy[b];
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> k;

    fcnt = vector<int>(n + 1, 1);
    candy = vector<int>(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> candy[i];
    
    parent = vector<int>(n + 1);
    for (int i = 1; i < n + 1; i++) parent[i] = i;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        unite(a, b);
    }

    vector<int> c; // cost = 친구 수
    vector<int> v; // value = 사탕 수

    for (int i = 1; i < n + 1; i++) {
        if (find(i) == i) {
            c.push_back(fcnt[i]);
            v.push_back(candy[i]);
        }
    }

    int newn = c.size();

    vector<int> dp(k, 0);
    for (int i = 0; i < newn; i++) {
        for (int j = k - 1; j >= 0; j--) {
            if (j - c[i] >= 0) dp[j] = max(dp[j], dp[j - c[i]] + v[i]);
        }
    }

    cout << dp[k - 1] << '\n';
}