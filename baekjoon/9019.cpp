#include <iostream>
#include <string>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int start, end;
        cin >> start >> end;

        vector<bool> vst(10000, false);
        queue<pair<int, string>> q;
        q.emplace(start, "");
        vst[start] = true;
        while (!q.empty()) {
            int curi = q.front().first;
            string curs = q.front().second;
            int nxti;
            q.pop();
            if (curi == end) {
                cout << curs << '\n';
                break;
            }
            // D
            nxti = (2 * curi) % 10000;
            if (!vst[nxti]) {
                q.emplace(nxti, curs + "D");
                vst[nxti] = true;
            }
            // S
            nxti = curi - 1;
            if (nxti < 0) nxti = 9999;
            if (!vst[nxti]) {
                q.emplace(nxti, curs + "S");
                vst[nxti] = true;
            }
            // L
            nxti = (curi * 10) % 10000;
            nxti += curi / 1000;
            if (!vst[nxti]) {
                q.emplace(nxti, curs + "L");
                vst[nxti] = true;
            }
            // R
            nxti = (curi % 10) * 1000;
            nxti += curi / 10;
            if (!vst[nxti]) {
                q.emplace(nxti, curs + "R");
                vst[nxti] = true;
            }
        }
    }
}