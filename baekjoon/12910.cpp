#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> c = vector<int>(51, 0);
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        c[tmp]++;
    }

    int ans = 0;
    int tmp = 1;

    for (int i = 1; i < 51; i++) {
        if (c[i] == 0) {
            break;
        }
        tmp *= c[i];
        ans += tmp;
    }

    cout << ans << '\n';
}