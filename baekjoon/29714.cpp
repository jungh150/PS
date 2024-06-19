#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    int total = n;
    map<int, int> ic;
    
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        if (ic.find(tmp) == ic.end()) {
            ic.insert({tmp, 1});
        } else {
            ic[tmp]++;
        }
    }

    int q;
    cin >> q;

    for (int tq = 0; tq < q; tq++) {
        int an, bn;

        cin >> an;
        vector<int> a(an);
        for (int i = 0; i < an; i++) {
            cin >> a[i];
        }

        cin >> bn;
        vector<int> b(bn);
        for (int i = 0; i < bn; i++) {
            cin >> b[i];
        }

        bool avail = true;

        for (int i = 0; i < an; i++) {
            if (ic.find(a[i]) == ic.end() || ic[a[i]] == 0) {
                avail = false;
                for (int j = 0; j < i; j++) {
                    ic[a[j]]++;
                    total++;
                }
                break;
            }
            ic[a[i]]--;
            total--;
        }

        if (avail) {
            for (int x: b) {
                ic[x]++;
                total++;
            }
        }
    }

    cout << total << endl;
    for (auto x: ic) {
        for (int i = 0; i < x.second; i++) {
            cout << x.first << ' ';
        }
    }
}