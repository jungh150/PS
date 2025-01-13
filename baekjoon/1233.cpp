#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int a, b, c;
    cin >> a >> b >> c;

    vector<int> cnt(a + b + c + 1, 0);
    int maxa = 0;
    int ans = 0;

    for (int i = 1; i < a + 1; i++) {
        for (int j = 1; j < b + 1; j++) {
            for (int k = 1; k < c + 1; k++) {
                cnt[i + j + k]++;
                if (cnt[i + j + k] > maxa) {
                    maxa = cnt[i + j + k];
                    ans = i + j + k;
                }
            }
        }
    }

    cout << ans << '\n';
}