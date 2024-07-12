#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> a;
vector<int> oa;

bool check() {
    if (oa.size() == n) {
        for (int i = 0; i < n; i++) {
            cout << oa[i] << ' ';
        }
        cout << '\n';
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    int pn = 1 << n;

    a = vector<int>(pn);
    for (int i = 0; i < pn; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    a.erase(a.begin()); // 0  삭제
    oa.push_back(a[0]);
    a.erase(a.begin());
    if (check()) return 0;

    while (true) {
        oa.push_back(a[0]);
        int newoa = a[0]; //2
        a.erase(a.begin());
        if (check()) return 0;

        int oas = oa.size() - 1; //2
        for (int i = 1; i < (1 << oas); i++) { //i = 1(01), 2(10), 3(11)
            int bm = i;
            int sumt = newoa; //2
            for (int j = 0; j < oas; j++) {
                if (bm % 2 == 1) sumt += oa[j];
                bm = bm >> 1;
            }
            for (int j = 0; j < a.size(); j++) {
                if (a[j] == sumt) {
                    a.erase(a.begin() + j);
                    break;
                }
            }
        }
    }
}