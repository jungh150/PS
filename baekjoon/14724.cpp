#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string club[] = {"PROBRAIN", "GROW", "ARGOS", "ADMIN", "ANT", "MOTION", "SPG", "COMON", "ALMIGHTY"};

    int n;
    cin >> n;

    int maxa = 0;
    int maxi = -1;
    for (int i = 0; i < 9; i++) {
        int tmp = 0;
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            tmp = max(tmp, x);
        }
        if (tmp > maxa) {
            maxa = tmp;
            maxi = i;
        }
    }

    cout << club[maxi] << '\n';
}