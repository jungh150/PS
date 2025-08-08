#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for (int i = 0; i < 8; i++) {
        int x;
        cin >> x;
        if (x == 9) {
            cout << "F\n";
            return 0;
        }
    }

    cout << "S\n";
}