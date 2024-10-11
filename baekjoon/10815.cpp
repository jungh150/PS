#include <iostream>
#include <set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;

    cin >> n;
    set<int> s;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        s.insert(x);
    }

    cin >> m;
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        if (s.find(x) != s.end()) cout << "1 ";
        else cout << "0 ";
    }
    cout << '\n';
}