#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int si = 0;
    int ei = 0;
    int maxcnt = 0;
    int cnt = 0;
    set<int> chk;

    while (chk.size() < 2 && ei < n) {
        chk.insert(a[ei]);
        cnt++;
        ei++;
    }
    maxcnt = cnt;

    if (chk.size() < 2) {
        cout << maxcnt << '\n';
        return 0;
    }

    while (ei < n) {
        while (chk.size() < 3 && ei < n) {
            chk.insert(a[ei]);
            ei++;
            cnt++;
            if (chk.size() == 2) {
                if (cnt > maxcnt) maxcnt = cnt;
            }
        }
        while (chk.size() > 2) {
            bool exist = false;
            for (int i = si + 1; i < ei; i++) {
                if (a[i] == a[si]) {
                    exist = true;
                    break;
                }
            }
            if (!exist) {
                chk.erase(a[si]);
            }
            si++;
            cnt--;
        }
        if (cnt > maxcnt) maxcnt = cnt;
    }

    cout << maxcnt << '\n';
}