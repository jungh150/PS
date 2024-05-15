#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    int minC = 0;
    int maxC = 0;

    if (n % 6 == 0) {
        minC = n / 2;
        maxC = 2 * n / 3;
    }
    else if (n % 2 == 0) {
        minC = n / 2;
        maxC = 2 * (n - 2) / 3 + 1;
    }
    else if (n % 3 == 0) {
        minC = (n - 1) / 2 + 1;
        maxC = 2 * n / 3;
    }
    else {
        minC = (n - 1) / 2 + 1;
        maxC = 2 * (n - 2) / 3 + 1;
    }

    cout << minC << ' ' << maxC << '\n';
}