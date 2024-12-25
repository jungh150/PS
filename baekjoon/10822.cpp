#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int sumt = 0;
    while (1) {
        int n;
        char c = ' ';
        cin >> n >> c;
        sumt += n;
        if (c != ',') break;
    }

    cout << sumt << '\n';
}