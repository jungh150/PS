#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<pair<int, int>> data(n);
    vector<int> ans = vector<int>(n);
    for (int i = 0; i < n; i++) {
        cin >> data[i].first;
        data[i].second = i;
    }

    sort(data.begin(), data.end());

    int cnt = 0;
    ans[data[0].second] = 0;
    int pre = data[0].first;
    for (int i = 1; i < n; i++) {
        if (data[i].first != pre) {
            cnt++;
        }
        ans[data[i].second] = cnt;
        pre = data[i].first;
    }

    for (int x: ans){
        cout << x << ' ';
    }
    cout << '\n';
}