#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    int n;
    cin >> s >> n;
    int sn = s.size();

    double ans = 0;
    string anss = "No Jam";

    while (n--) {
        string a;
        double g;
        cin >> a >> g;
        int an = a.size();

        int cnt = 0;
        int idx1 = 0;
        int idx2 = 0;

        bool psb = true;
        while (idx2 < an) {
            if (idx1 < sn && s[idx1] == a[idx2]) {
                idx1++;
                idx2++;
            } else {
                idx2++;
                cnt++;
            }
        }

        if (idx1 == sn) {
            double tmp = g / cnt;
            if (tmp > ans) {
                ans = tmp;
                anss = a;
            }
        }
    }

    cout << anss << '\n';
}