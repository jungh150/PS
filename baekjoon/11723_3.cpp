#include <iostream>
#include <set>
using namespace std;

int chk[21];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int m, n;
    string op;
    cin >> m;

    for (int i = 0; i < m; i++) {
        cin >> op;
        if (op == "add") {
            cin >> n;
            chk[n] = true;
        } else if (op == "remove") {
            cin >> n;
            chk[n] = false;
        } else if (op == "check") {
            cin >> n;
            if (chk[n]) cout << 1 << '\n';
            else cout << 0 << '\n';
        } else if (op == "toggle") {
            cin >> n;
            if (chk[n]) chk[n] = false;
            else chk[n] = true;
        } else if (op == "all") {
            for (int i = 0; i < 21; i++) chk[i] = true;
        } else if (op == "empty") {
            for (int i = 0; i < 21; i++) chk[i] = false;
        }
    }
}