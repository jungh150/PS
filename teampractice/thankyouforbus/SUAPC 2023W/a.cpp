#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<pair<string, char>> a(8);
    for (int i = 0; i < 8; i++) {
        cin >> a[i].first >> a[i].second;
    }

    sort(a.begin(), a.end());
    
}