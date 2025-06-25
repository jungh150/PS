#include <iostream>
#include <vector>
using namespace std;

int g, p;
vector<int> a;
vector<int> parent;

int find(int a) {
    if (parent[a] == a) return a;
    else return parent[a] = find(parent[a]);
}

void unite(int a, int b) { // a < b
    a = find(a);
    b = find(b);
    if (a != b) parent[b] = a;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> g >> p;
    
    a = vector<int>(p);
    for (int i = 0; i < p; i++) cin >> a[i];

    parent = vector<int>(g + 1);
    for (int i = 0; i < g + 1; i++) parent[i] = i;

    int ans = 0;
    for (int i = 0; i < p; i++) {
        int target = find(a[i]);
        if (target > 0) {
            ans++;
            unite(target - 1, target);
        } else {
            break;
        }
    }
    cout << ans << '\n';
}