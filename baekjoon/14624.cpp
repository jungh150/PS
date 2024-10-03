#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    if (n % 2 == 0) {
        cout << "I LOVE CBNU\n";
    } else {
        for (int i = 0; i < n; i++) cout << '*';
        cout << '\n';
        for (int i = 0; i < (n - 1) / 2; i++) cout << ' ';
        cout << "*\n";
        for (int i = 0; i < (n - 1) / 2; i++) {
            for (int j = 0; j < (n - 3) / 2 - i; j++) cout << ' ';
            cout << "* ";
            for (int j = 0; j < 2 * i; j++) cout << ' ';
            cout << "*\n";
        }
    }
}