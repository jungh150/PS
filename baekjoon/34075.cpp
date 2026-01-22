#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<pair<string, int>> al(n);
    for (int i = 0; i < n; i++) cin >> al[i].first >> al[i].second;

    map<string, pair<string, string>> ans;
    int m;
    cin >> m;
    while (m--) {
        string name;
        int tier;
        cin >> name >> tier;

        vector<pair<int, string>> tmp;
        for (int i = 0; i < n; i++) {
            tmp.emplace_back(abs(tier - al[i].second), al[i].first);
        }
        sort(tmp.begin(), tmp.end());

        ans[name] = {tmp[0].second, tmp[1].second};
    }

    int q;
    cin >> q;
    string rec = "";
    string s;
    getline(cin, s); // cin 입력으로 인해 남은 개행 문자 처리
    while (q--) {
        getline(cin, s);
        if (s == "nani ga suki?") {
            cout << ans[rec].second << " yori mo " << ans[rec].first << '\n';
        } else {
            for (int i = 0; i < 8; i++) s.pop_back();
            rec = s;
            cout << "hai!\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}