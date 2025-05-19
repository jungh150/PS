#include <iostream>
#include <vector>
using namespace std;

int n, q;
vector<pair<int, int>> a;
vector<vector<int>> sop;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> q;
    a = vector<pair<int, int>>(4);
    sop = vector<vector<int>>();

    a[0] = make_pair(1, 1);
    a[1] = make_pair(1, 2);
    a[2] = make_pair(2, 1);
    a[3] = make_pair(2, 2);

    while (q--) {
        string s;
        cin >> s;
        if (s == "RO") {
            int sopn = sop.size();
            for (int i = 0; i < sopn; i++) {
                if (sop[i][0] % 2 == 1) sop[i][1] = sop[i][1] % n + 1;
                if (sop[i][2] % 2 == 1) sop[i][3] = sop[i][3] % n + 1;
            }
            for (int i = 0; i < 4; i++) {
                if (a[i].first % 2 == 1) a[i].second = a[i].second % n + 1;
            }
        } else if (s == "RE") {
            int sopn = sop.size();
            for (int i = 0; i < sopn; i++) {
                if (sop[i][0] % 2 == 0) sop[i][1] = sop[i][1] % n + 1;
                if (sop[i][2] % 2 == 0) sop[i][3] = sop[i][3] % n + 1;
            }
            for (int i = 0; i < 4; i++) {
                if (a[i].first % 2 == 0) a[i].second = a[i].second % n + 1;
            }
        } else if (s == "CO") {
            int sopn = sop.size();
            for (int i = 0; i < sopn; i++) {
                if (sop[i][1] % 2 == 1) sop[i][0] = sop[i][0] % n + 1;
                if (sop[i][3] % 2 == 1) sop[i][2] = sop[i][2] % n + 1;
            }
            for (int i = 0; i < 4; i++) {
                if (a[i].second % 2 == 1) a[i].first = a[i].first % n + 1;
            }
        } else if (s == "CE") {
            int sopn = sop.size();
            for (int i = 0; i < sopn; i++) {
                if (sop[i][1] % 2 == 0) sop[i][0] = sop[i][0] % n + 1;
                if (sop[i][3] % 2 == 0) sop[i][2] = sop[i][2] % n + 1;
            }
            for (int i = 0; i < 4; i++) {
                if (a[i].second % 2 == 0) a[i].first = a[i].first % n + 1;
            }
        } else {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            sop.push_back({r1, c1, r2, c2});
        }
    }

    vector<vector<int>> ans(n + 1, vector<int>(n + 1, -1));

    for (int i = 0; i < n; i += 2) {
        for (int j = 0; j < n; j += 2) {
            ans[(a[0].first + i - 1) % n + 1][(a[0].second + j - 1) % n + 1] = n * i + 1 + j;
        }
    }

    for (int i = 0; i < n; i += 2) {
        for (int j = 0; j < n; j += 2) {
            ans[(a[1].first + i - 1) % n + 1][(a[1].second + j - 1) % n + 1] = n * i + 2 + j;
        }
    }

    for (int i = 0; i < n; i += 2) {
        for (int j = 0; j < n; j += 2) {
            ans[(a[2].first + i - 1) % n + 1][(a[2].second + j - 1) % n + 1] = n * i + n + 1 + j;
        }
    }

    for (int i = 0; i < n; i += 2) {
        for (int j = 0; j < n; j += 2) {
            ans[(a[3].first + i - 1) % n + 1][(a[3].second + j - 1) % n + 1] = n * i + n + 2 + j;
        }
    }

    int sopn = sop.size();
    for (int i = 0; i < sopn; i++) {
        int tmp = ans[sop[i][0]][sop[i][1]];
        ans[sop[i][0]][sop[i][1]] = ans[sop[i][2]][sop[i][3]];
        ans[sop[i][2]][sop[i][3]] = tmp;
    }

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }
}