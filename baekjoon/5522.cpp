#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int sumt = 0;
    for (int i = 0; i < 5; i++) {
        int tmp;
        cin >> tmp;
        sumt += tmp;
    }

    cout << sumt << '\n';
}