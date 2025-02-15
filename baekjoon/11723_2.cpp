#include <iostream>
#include <set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int m, n;
    string op;
    cin >> m;
    set<int> s;

    for (int i = 0; i < m; i++) {
        cin >> op;
        if (op == "add") {
            cin >> n;
            s.insert(n);
        } else if (op == "remove") {
            cin >> n;
            s.erase(n);
        } else if (op == "check") {
            cin >> n;
            if (s.find(n) == s.end()) cout << 0 << '\n';
            else cout << 1 << '\n';
        } else if (op == "toggle") {
            cin >> n;
            if (s.find(n) == s.end()) s.insert(n);
            else s.erase(n);
        } else if (op == "all") {
            s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
        } else if (op == "empty") {
            s = {};
        }
    }
}