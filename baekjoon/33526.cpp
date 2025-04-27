#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << 'N';
        for (int j = 0; j < n; j++) cout << 'A';
        for (int j = 0; j < n; j++) cout << 'Z';
        cout << '\n';
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << 'A';
        for (int j = 0; j < n; j++) cout << 'Z';
        for (int j = 0; j < n; j++) cout << 'N';
        cout << '\n';
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << 'Z';
        for (int j = 0; j < n; j++) cout << 'N';
        for (int j = 0; j < n; j++) cout << 'A';
        cout << '\n';
    }
}