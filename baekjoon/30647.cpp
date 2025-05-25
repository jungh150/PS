#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<tuple<int, string, bool>> par;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        int idx = 0;

        string name = "";
        while (s[idx] != '\"') idx++;
        idx++;
        while (s[idx] != '\"') idx++;
        idx++;
        while (s[idx] != '\"') idx++;
        idx++;
        while (s[idx] != '\"') {
            name += s[idx];
            idx++;
        }
        idx += 10;

        string score = "";
        while (s[idx] != ',') {
            score += s[idx];
            idx++;
        }
        idx += 12;

        bool isHidden;
        if (s[idx] == '1') isHidden = true;
        else isHidden = false;

        par.push_back({-stoi(score), name, isHidden});
    }

    sort(par.begin(), par.end());

    int pre = 1;
    for (int i = 0; i < n; i++) {
        if (i >= 1 && get<0>(par[i]) == get<0>(par[i - 1])) {
            if (!get<2>(par[i])) cout << pre << ' ';
        } else {
            if (!get<2>(par[i])) cout << i + 1 << ' ';
            pre = i + 1;
        }

        if (!get<2>(par[i])) {
            cout << get<1>(par[i]) << ' ' << -get<0>(par[i]) << '\n';
        }
    }
}