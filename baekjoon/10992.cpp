#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n - 1; i++) cout << ' ';
    cout << "*\n";

    for (int i = 2; i < n; i++) {
        for (int j = 0; j < n - i; j++) cout << ' ';
        cout << '*';
        for (int j = 0; j < 2 * i - 3; j++) cout << ' ';
        cout << "*\n";
    }

    if (n > 1) {
        for (int i = 0; i < 2 * n - 1; i++) cout << '*';
        if (n > 1) cout << '\n';
    }
}