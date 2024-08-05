#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;
    char str[n];

    int i = 0; // idx
    for (; i < (n - k); i++) str[i] = 'a';
    for (int j = 0; j < k; j++) {
        if (i >= n) break;
        str[i] = 'a' + j;
        i++;
    }

    for (i = 0; i < n; i++) cout << str[i];
    cout << '\n';
}