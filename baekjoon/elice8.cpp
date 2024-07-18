#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Event {
    int time;
    int type;
    Event(int t, int tp) : time(t), type(tp) {}
};

bool compareEvent(const Event &a, const Event &b) {
    if (a.time == b.time) return a.type > b.type;
    return a.time < b.time;
}

int main() {
    int n, m, k, t;
    cin >> n >> m >> k >> t;

    vector<Event> e;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        e.push_back(Event(a, 1));
        e.push_back(Event(b, -1));
    }

    sort(e.begin(), e.end(), compareEvent);

    vector<int> dp(n + 2, 0);
    int curp = 0;
    int maxt = 0;
    int pre = 1;

    for (auto &event : e) {
        int curt = event.time;
        
        if (curp >= t) {
            maxt += curt - pre;
        }

        curp += event.type;
        pre = curt;
    }

    curp = 0;
    pre = 1;
    int cnt = 0;

    for (auto &event : e) {
        int curt = event.time;

        if (curp >= t) {
            maxt += curt - pre;
        } else if (curp + k >= t) {
            maxt += curt - pre;
            cnt++;
            if (cnt == k) break;
        }

        curp += event.type;

        pre = curt;
    }

    cout << maxt << '\n';
}
