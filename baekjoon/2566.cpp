#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int maxa = 0;
    int maxi = 1;
    int maxj = 1;
    for (int i = 1; i < 10; i++) {
        for (int j = 1; j < 10; j++) {
            int x;
            cin >> x;
            if (x > maxa) {
                maxa = x;
                maxi = i;
                maxj = j;
            }
        }
    }

    cout << maxa << '\n' << maxi << ' ' << maxj << '\n';
}