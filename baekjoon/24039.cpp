#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<bool> p(n + 10, true);
    p[1] = false;
    for (int i = 2; i < n + 10; i++) {
        int tmp = i + i;
        while (tmp < n + 1) {
            p[tmp] = false;
            tmp += i;
        }
    }

    int pre = 2;
    int cur = 3;
    for (int i = 3; i < n + 10; i++) {
        if (!p[i]) continue;
        cur = i;
        int mul = pre * cur;
        if (mul > n) {
            cout << mul << '\n';
            return 0;
        } else {
            mul /= pre;
            pre = cur;
        }
    }
}