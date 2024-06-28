#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> sp1(n);
    vector<int> sp2(n);
    for (int i = 0; i < n; i++) {
        cin >> sp1[i];
        if (sp1[i] == 1) sp2[n - i - 1] = 3;
        else if (sp1[i] == 2) sp2[n - i - 1] = 4;
        else if (sp1[i] == 3) sp2[n - i - 1] = 1;
        else if (sp1[i] == 4) sp2[n - i - 1] = 2;
    }

    int t;
    cin >> t;
    vector<vector<int>> tp(t, vector<int>(n));
    vector<int> ans;

    for (int k = 0; k < t; k++) {
        for (int i = 0; i < n; i++) {
            cin >> tp[k][i];
        }

        bool chk;
        for (int i = 0; i < n; i++) {
            chk = true;
            for (int j = 0; j < n; j++) {
                if (sp1[j] != tp[k][(j + i) % n]) {
                    chk = false;
                    break;
                }
            }
            if (chk) break;
        }

        if (chk) {
            ans.push_back(k);
            continue;
        }

        for (int i = 0; i < n; i++) {
            chk = true;
            for (int j = 0; j < n; j++) {
                if (sp2[j] != tp[k][(j + i) % n]) {
                    chk = false;
                    break;
                }
            }
            if (chk) break;
        }

        if (chk) {
            ans.push_back(k);
        }
    }

    cout << ans.size() << '\n';
    for (int k = 0; k < ans.size(); k++) {
        for (int i = 0; i < n; i++) {
            cout << tp[ans[k]][i] << ' ';
        }
        cout << '\n';
    }
}