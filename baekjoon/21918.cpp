#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<bool> bulb(n + 1);
    for (int i = 1; i < n + 1; i++) {
        int tmp;
        cin >> tmp;
        bulb[i] = tmp;
    }

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 1) {
            bulb[b] = c;
        } else if (a == 2) {
            for (int j = b; j < c + 1; j++) {
                if (bulb[j]) bulb[j] = false;
                else bulb[j] = true;
            }
        } else if (a == 3) {
            for (int j = b; j < c + 1; j++) {
                bulb[j] = false;
            }
        } else {
            for (int j = b; j < c + 1; j++) {
                bulb[j] = true;
            }
        }
    }

    for (int i = 1; i < n + 1; i++) {
        cout << (int) bulb[i] << ' ';
    }
    cout << '\n';
}