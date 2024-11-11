#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool vst[300001];
int dx[] = {1, -1};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    queue<pair<int, int>> q;
    int cur, cnt;
    bool fin = false;

    q.emplace(n, 0);
    vst[n + 100000] = true;
    while (!fin) {
        cur = q.front().first;
        cnt = q.front().second;
        if (cur == k) {
            fin = true;
            break;
        }
        q.pop();
        int tmp = cur;
        while (tmp >= -100000 && tmp <= 200000) {
            for (int k = 0; k < 2; k++) {
                int nxt = tmp + dx[k];
                if (nxt >= -100000 && nxt <= 200000 &&  !vst[nxt + 100000]) {
                    q.emplace(nxt, cnt + 1);
                    vst[nxt + 100000] = true;
                }
            }
            tmp *= 2;
            if (tmp == k) {
                fin = true;
                break;
            }
            if (tmp == 0) break;
        }
    }

    cout << cnt << '\n';
}