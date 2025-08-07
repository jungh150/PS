#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<pair<string, string>> a(8);
    for (int i = 0; i < 8; i++) cin >> a[i].first >> a[i].second;

    sort(a.begin(), a.end());

    int reds = 0;
    int blues = 0;

    if (a[0].second == "R") reds += 10;
    else blues += 10;

    if (a[1].second == "R") reds += 8;
    else blues += 8;

    if (a[2].second == "R") reds += 6;
    else blues += 6;

    if (a[3].second == "R") reds += 5;
    else blues += 5;

    if (a[4].second == "R") reds += 4;
    else blues += 4;

    if (a[5].second == "R") reds += 3;
    else blues += 3;

    if (a[6].second == "R") reds += 2;
    else blues += 2;

    if (a[7].second == "R") reds += 1;
    else blues += 1;

    if (blues > reds) {
        cout << "Blue\n";
    } else if (blues < reds) {
        cout << "Red\n";
    } else {
        if (a[0].second == "B") cout << "Blue\n";
        else cout << "Red\n";
    }
}