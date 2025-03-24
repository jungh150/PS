#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        if (n == 1) {
            cout << 0 << '\n';
        } else {
            cout << 1;
            for (int i = 0; i < n - 2; i++) cout << 2;
            cout << 1 << '\n';
        }
    }
}