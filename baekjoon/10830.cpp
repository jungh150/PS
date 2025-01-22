#include <iostream>
#include <vector>
using namespace std;

int n;
long long b;
int mod = 1000;

vector<vector<int>> mpow(vector<vector<int>> a, long long c) {
    vector<vector<int>> res(n, vector<int>(n));

    if (c == 1) {
        return a;
    } else if (c % 2 == 0) {
        vector<vector<int>> tmp = mpow(a, c / 2);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int rest = 0;
                for (int k = 0; k < n; k++) {
                    rest += tmp[i][k] * tmp[k][j];
                    rest %= mod;
                }
                res[i][j] = rest;
            }
        }
    } else {
        vector<vector<int>> tmp = mpow(a, c - 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int rest = 0;
                for (int k = 0; k < n; k++) {
                    rest += tmp[i][k] * a[k][j];
                    rest %= mod;
                }
                res[i][j] = rest;
            }
        }
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> b;

    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            a[i][j] %= mod;
        }
    }

    vector<vector<int>> ans = mpow(a, b);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }
}