#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    if (k < 8) {
        int now = n;
        while (true) {
            now++;
            set<int> s;
            int tmp = now;
            while (tmp > 0) {
                s.insert(tmp % 10);
                tmp /= 10;
            }
            if (s.size() == k) break;
        }
        cout << now << '\n';
    } else if (k == 8) {
        cout << 10234567 << '\n';
    } else if (k == 9) {
        cout << 102345678 << '\n';
    } else if (k == 10) {
        cout << 1023456789 << '\n';
    }
}