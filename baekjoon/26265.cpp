#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(pair<string, string> a, pair<string, string> b) {
    if (a.first == b.first) return a.second > b.second;
    return a.first < b.first;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<pair<string, string>> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i].first >> arr[i].second;

    sort(arr.begin(), arr.end(), compare);

    for (int i = 0; i < n; i++) cout << arr[i].first << ' ' << arr[i].second << '\n';
}