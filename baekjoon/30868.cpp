#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        int q = n / 5;
        for (int j = 0; j < q; j++) cout << "++++ ";
        int r = n % 5;
        for (int j = 0; j < r; j++) cout << "|";
        cout << '\n';
    }
}