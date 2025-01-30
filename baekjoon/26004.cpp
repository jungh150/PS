#include <iostream>
#include <vector>
using namespace std;

int cnt[5];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    while (n--) {
        char c;
        cin >> c;

        if (c == 'H') cnt[0]++;
        else if (c == 'I') cnt[1]++;
        else if (c == 'A') cnt[2]++;
        else if (c == 'R') cnt[3]++;
        else if (c == 'C') cnt[4]++;
    }

    int ans = 100000;
    for (int i = 0; i < 5; i++) ans = min(ans, cnt[i]);
    cout << ans << '\n';
}