#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    for (int i = 2 * n - 1; i > 0; i -= 2) {
        for (int j = 0; j < (2 * n - 1 - i) / 2; j++) cout << " ";
        for (int j = 0; j < i; j++) cout << "*";
        cout << '\n';
    }
    for (int i = 3; i < 2 * n; i += 2) {
        for (int j = 0; j < (2 * n - 1 - i) / 2; j++) cout << " ";
        for (int j = 0; j < i; j++) cout << "*";
        cout << '\n';
    }
}