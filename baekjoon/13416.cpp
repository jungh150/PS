#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tn;
    cin >> tn;

    while (tn--) {
        int n;
        cin >> n;

        long long total = 0;
        for (int i = 0; i < n; i++) {
            int maxt = 0;
            for (int j = 0; j < 3; j++) {
                int itr;
                cin >> itr;
                if (itr > maxt) maxt = itr;
            }
            total += maxt;
        }
        cout << total << '\n';
    }
}