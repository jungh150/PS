#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int a, p;
    cin >> a >> p;

    vector<int> ans;
    ans.push_back(a);

    int idx = -1;
    int cur = a;

    while (1) {
        int nxt = 0;

        while (cur > 0) {
            int rem = cur % 10;
            int tmp = 1;
            for (int i = 0; i < p; i++) tmp *= rem;
            nxt += tmp;
            cur /= 10;
        }
        
        int ansn = ans.size();
        for (int i = 0; i < ansn; i++) {
            if (ans[i] == nxt) {
                idx = i;
                break;
            }
        }

        if (idx != -1) break;

        ans.push_back(nxt);
        cur = nxt;
    }

    cout << idx << '\n';
}