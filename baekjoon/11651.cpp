#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// y 기준으로 오름차순, 같으면 x 기준으로 오름차순
bool compare(pair<int,int> &a, const pair<int,int> &b) {
    if (a.second == b.second) return a.first < b.first; // y 같으면 x 기준
    else return a.second < b.second; // y 기준
}

void solve() {
    int n;
    cin >> n;

    vector<pair<int, int>> data(n);
    for (int i = 0; i < n; i++) cin >> data[i].first >> data[i].second;

    sort(data.begin(), data.end(), compare);

    for (auto d: data) cout << d.first << ' ' << d.second << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}