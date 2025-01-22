#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, a, b;
    cin >> n >> a >> b;

    int at = 1;
    int bt = 1;

    while (n--) {
        at += a;
        bt += b;
        if (bt > at) {
            int tmp = bt;
            bt = at;
            at = tmp;
        } else if (at == bt) {
            bt--;
        }
    }

    cout << at << ' ' << bt << '\n';
}