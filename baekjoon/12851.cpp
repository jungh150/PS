#include <iostream>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    int maxs = 100001;
    vector<bool> vst = vector<bool>(maxs, false);

    int timea = 0;
    int cnt = 0;
    queue<pair<int, int>> q;
    q.emplace(n, 0);
    vst[n] = true;

    while (!q.empty()) {
        int cur = q.front().first;
        int time = q.front().second;
        q.pop();

        if (cur == k && !vst[cur]) {
            timea = time;
            cnt++;
        } else if (cur == k && time == timea) {
            cnt++;
        }

        vst[cur] = true; // 여기서 방문 처리

        if ((cur - 1) >= 0 && (cur - 1) < maxs) {
            if (vst[cur - 1] == 0) q.emplace(cur - 1, time + 1);
        }
        if ((cur + 1) >= 0 && (cur + 1) < maxs) {
            if (vst[cur + 1] == 0) q.emplace(cur + 1, time + 1);
        }
        if ((cur * 2) >= 0 && (cur * 2) < maxs) {
            if (vst[cur * 2] == 0) q.emplace(cur * 2, time + 1);
        }
    }

    cout << timea << '\n' << cnt << '\n';
}