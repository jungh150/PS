#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a;

    int pre = -1;
    int cur;
    int cnt = 1;
    for (int i = 0; i < n; i++) {
        cin >> cur;
        if (i != 0) {
            if (cur == pre) {
                cnt++;
            } else {
                a.push_back(cnt);
                cnt = 1;
            }
        }
        pre = cur;
    }
    a.push_back(cnt);

    int an = a.size();
    int maxa = a[0];
    for (int i = 1; i < an; i++) {
        maxa = max(maxa, a[i - 1] + a[i]);
    }

    cout << maxa << '\n';
}