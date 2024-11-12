#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    int mint = 1000000000;
    int maxt = 0;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x < mint) mint = x;
        if (x > maxt) maxt = x;
    }

    cout << 2 * (maxt - mint) << '\n';
}