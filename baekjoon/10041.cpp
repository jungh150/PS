#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int dst(int si, int sj, int ei, int ej) {
    if ((ei - si) * (ej - sj) > 0) {
        int dia = min(abs(ei - si), abs(ej - sj));
        if (ei - si > 0) {
            si += dia;
            sj += dia;
        } else {
            si -= dia;
            sj -= dia;
        }
        int str = max(abs(ei - si), abs(ej - sj));
        return dia + str;
    } else {
        return abs(ei - si) + abs(ej - sj);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int w, h, n;
    cin >> w >> h >> n;

    vector<pair<int, int>> at(n);
    for (int i = 0; i < n; i++) {
        cin >> at[i].first >> at[i].second;
    }

    int ans = 0;
    for (int i = 0; i < n - 1; i++) {
        ans += dst(at[i].first, at[i].second, at[i + 1].first, at[i + 1].second);
    }

    cout << ans << '\n';
}