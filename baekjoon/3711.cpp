#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    while (n--) {
        int g;
        cin >> g;

        vector<int> a(g);
        for (int i = 0; i < g; i++) cin >> a[i];

        int m = g;

        while (1) {
            set<int> s;
            bool fin = false;

            for (int i = 0; i < g; i++) {
                int rem = a[i] % m;
                if (s.find(rem) == s.end()) {
                    s.insert(rem);
                } else {
                    fin = true;
                    break;
                }
            }

            if (!fin) {
                cout << m << '\n';
                break;
            }

            m++;
        }
    }
}