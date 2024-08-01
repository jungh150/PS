#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    while (true) {
        int n;
        cin >> n;
        if (n == 0) break;

        int i = 1;
        while (i <= n) {
            bool eq = false;
            vector<bool> chk(10, false);
            string str = to_string(i);
            for (char c: str) {
                if (chk[c - '0']) {
                    eq = true;
                    break;
                } else {
                    chk[c - '0'] = true;
                }
            }
            if (eq) {
                n++;
            }
            i++;
        }

        cout << n << '\n';
    }
}