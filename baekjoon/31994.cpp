#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    int n = 0;

    for (int i = 0; i < 7; i++) {
        string tmps;
        int tmpn;
        cin >> tmps >> tmpn;

        if (tmpn > n) {
            n = tmpn;
            s = tmps;
        }
    }

    cout << s << '\n';
}