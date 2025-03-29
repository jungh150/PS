#include <iostream>
#include <vector>
#include <map>
using namespace std;

int pow2[] = {1, 2, 4, 8, 16, 32, 64, 128};
int a[] = {0, 1, 2, 3, 4, 5, 6, 7}; // i번 키의 현재 위치

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    map<int, pair<int, int>> m;
    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 8; j++) {
            int tmp = pow2[i] + pow2[j];
            m[tmp] = make_pair(i, j);
        }
    }

    int n;
    cin >> n;

    while (n--) {
        int cmd;
        cin >> cmd;

        if (m.find(cmd) != m.end()) {
            int i = m[cmd].first;
            int j = m[cmd].second;
            int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }
    }

    int k;
    cin >> k;

    cout << a[k] << '\n';
}