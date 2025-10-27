#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void solve() {
    int n, t, g;
    cin >> n >> t >> g;

    vector<bool> vst(1e5, false);
    queue<pair<int, int>> q;

    q.emplace(n, 0);
    vst[n] = true;
    while (!q.empty()) {
        auto [cur, cnt] = q.front();
        q.pop();
        if (cur == g && cnt <= t) {
            cout << cnt << '\n';
            return;
        }

        int nxt = cur + 1;
        if (nxt < 1e5 && !vst[nxt]) {
            q.emplace(nxt, cnt + 1);
            vst[nxt] = true;
        }

        int tmp = cur * 2;
        if (tmp == 0) {
            nxt = 0;
        } else {
            string tmps = to_string(tmp);
            tmps[0] = tmps[0] - 1;
            nxt = stoi(tmps);
        }
        if (tmp < 1e5 && !vst[nxt]) {
            q.emplace(nxt, cnt + 1);
            vst[nxt] = true;
        }
    }

    cout << "ANG\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}