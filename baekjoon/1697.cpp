#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    int maxs = 100001;
    vector<bool> vst = vector<bool>(maxs, false);

    int cnt = 0;
    bool fin = false;
    queue<int> q;
    q.push(n);
    vst[n] = true;
    
    while(!q.empty()) {
        int tmp = q.size();
        for (int i = 0; i < tmp; i++) {
            int cur = q.front();
            q.pop();
            if (cur == k) {
                fin = true;
            }
            if ((cur - 1) >= 0 && (cur - 1) < maxs) {
                if (!vst[cur - 1]) {
                    q.push(cur - 1);
                    vst[cur - 1] = true;
                }
            }
            if ((cur + 1) >= 0 && (cur + 1) < maxs) {
                if (!vst[cur + 1]) {
                    q.push(cur + 1);
                    vst[cur + 1] = true;
                }
            }
            if ((cur * 2) >= 0 && (cur * 2) < maxs) {
                if (!vst[cur * 2]) {
                    q.push(cur * 2);
                    vst[cur * 2] = true;
                }
            }
        }
        if (fin) {
            break;
        }
        cnt++;
    }

    cout << cnt << '\n';
}