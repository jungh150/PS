#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    map<string, int> cnt;

    while (n--) {
        int s, t;
        cin >> s >> t;
        while (t--) {
            string tag;
            cin >> tag;
            
            if (cnt.find(tag) == cnt.end()) cnt[tag] = 0;
            else cnt[tag]++;
        }
    }

    vector<pair<string, int>> v(cnt.begin(), cnt.end());

    sort(v.begin(), v.end(), [](const pair<string, int> &a, const pair<string, int> &b) {
        return a.second > b.second;
    });

    if (cnt.size() > 1 && v[0].second == v[1].second) cout << "-1\n";
    else cout << v[0].first << '\n';
}