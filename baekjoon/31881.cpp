#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;

    vector<bool> com(n + 1, 0);
    int cnt = n;

    while (q--) {
        int qn;
        cin >> qn;

        if (qn == 1) {
            int x;
            cin >> x;
            if (!com[x]) {
                com[x] = 1;
                cnt--;
            }
        } else if (qn == 2) {
            int x;
            cin >> x;
            if (com[x]) {
                com[x] = 0;
                cnt++;
            }
        } else if (qn == 3) {
            cout << cnt << '\n';
        }
    }
}