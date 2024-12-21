#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<int> cnt(26, 0);
    int anscnt = 0;
    int anstime = 0;

    while (1) {
        int m;
        cin >> m;
        if (m == -1) break;

        char p;
        string r;
        cin >> p >> r;

        if (r == "right") {
            anscnt++;
            anstime += (m + cnt[p - 'A'] * 20);
        } else if (r == "wrong") {
            cnt[p - 'A']++;
        }
    }

    cout << anscnt << ' ' << anstime << '\n';
}