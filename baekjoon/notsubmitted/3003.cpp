#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int o[6] = {1, 1, 2, 2, 2, 8};

    for (int i = 0; i < 6; i++) {
        int cur;
        cin >> cur;
        cout << o[i] - cur << ' ';
    }
    cout << '\n';
}