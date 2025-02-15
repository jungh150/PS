#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int m, n;
    string op;
    cin >> m;
    int now = 0;

    for (int i = 0; i < m; i++) {
        cin >> op;
        if (op == "add") {
            cin >> n;
            now = now | (1 << (n - 1));
        } else if (op == "remove") {
            cin >> n;
            if ((now & (1 << (n - 1))) != 0) {
                now = now ^ (1 << (n - 1));
            }
        } else if (op == "check") {
            cin >> n;
            if ((now & (1 << (n - 1))) == 0) cout << 0 << '\n';
            else cout << 1 << '\n';
        } else if (op == "toggle") {
            cin >> n;
            now = now ^ (1 << (n - 1));
        } else if (op == "all") {
            now = -1;
        } else if (op == "empty") {
            now = 0;
        }
    }
}