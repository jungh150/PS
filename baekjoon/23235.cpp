#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int idx = 1;
    while (1) {
        int n;
        cin >> n;

        if (n == 0) break;

        int x;
        while (n--) cin >> x;

        cout << "Case " << idx << ": Sorting... done!\n";
        idx++;
    }
}