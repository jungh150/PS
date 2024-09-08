#include <iostream>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int move[111];
    for (int i = 0; i < 111; i++) move[i] = i;

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n + m; i++) {
        int a, b;
        cin >> a >> b;
        move[a] = b;
    }

    bool vst[111] = {};
    vst[0] = true;
    queue<pair<int, int>> q; // <position, time>
    q.emplace(1, 0);
    vst[1] = true;
    while (1) {
        int pos = q.front().first;
        int t = q.front().second;
        q.pop();
        if (pos == 100) {
            cout << t << '\n';
            break;
        }
        for (int i = 1; i < 7; i++) {
            if (move[pos + i] <= 100 && vst[pos + i] == false) {
                q.emplace(move[pos + i], t + 1);
                vst[pos + i] = true;
            }
        }
    }
}