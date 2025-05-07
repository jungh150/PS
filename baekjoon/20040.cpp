#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> parent;

int find(int a) {
    if (parent[a] == a) return a;
    else return parent[a] = find(parent[a]);
}

int unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        parent[b] = a;
        return true;
    } else {
        return false; // 사이클 발생
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    
    parent = vector<int>(n + 1);
    for (int i = 0; i < n; i++) parent[i] = i;

    for (int i = 1; i < m + 1; i++) {
        int a, b;
        cin >> a >> b;
        if (!unite(a, b)) {
            cout << i << '\n';
            return 0;
        }
    }

    cout << "0\n";
}