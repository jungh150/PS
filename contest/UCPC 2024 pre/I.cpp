#include <iostream>
#include <map>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    int cnt = 0;
    map<int, bool> vst;
    queue<int> q;

    q.push(0);
    vst.insert({0, true});
    cnt++;

    while (n--) {
        string str;
        cin >> str;
        if (str == "L") {
            int qs = q.size();
            while (qs--) {
                int cur = q.front();
                q.pop();
                q.push(cur);
                int nxt = cur - 1;
                if (vst.find(nxt) == vst.end()) { // 없다면
                    q.push(nxt);
                    vst.insert({nxt, true});
                    cnt++;
                }
            }
        } else if (str == "R") {
            int qs = q.size();
            while (qs--) {
                int cur = q.front();
                q.pop();
                q.push(cur);
                int nxt = cur + 1;
                if (vst.find(nxt) == vst.end()) { // 없다면
                    q.push(nxt);
                    vst.insert({nxt, true});
                    cnt++;
                }
            }
        } else if (str == "C") {
            int x;
            cin >> x;
            if (vst.find(x) == vst.end()) {
                q.push(x);
                vst.insert({x, true});
                cnt++;
            }
        } else if (str == "Q") {
            cout << cnt <<'\n';
        }
    }
}