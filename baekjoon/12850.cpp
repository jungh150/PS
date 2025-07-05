#include <iostream>
#include <vector>
using namespace std;

int MOD = 1000000007;
vector<vector<long long>> e;

vector<vector<long long>> mul(vector<vector<long long>> a, vector<vector<long long>> b) {
    vector<vector<long long>> c(8, vector<long long>(8, 0));
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 8; k++) {
                c[i][j] += (a[i][k] * b[k][j]);
                c[i][j] = c[i][j] % MOD;
            }
        }
    }
    return c;
}

vector<vector<long long>> pow(vector<vector<long long>> a, int x) {
    if (x == 1) return a;
    vector<vector<long long>> half = pow(a, x / 2);
    if (x % 2 == 0) return mul(half, half);
    else return mul(mul(half, half), a);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int d;
    cin >> d;

    e = {{0, 1, 0, 1, 0, 0, 0, 0},
         {1, 0, 1, 1, 0, 0, 0, 0},
         {0, 1, 0, 1, 1, 1, 0, 0},
         {1, 1, 1, 0, 0, 1, 0, 0},
         {0, 0, 1, 0, 0, 1, 1, 0},
         {0, 0, 1, 1, 1, 0, 0, 1},
         {0, 0, 0, 0, 1, 0, 0, 1},
         {0, 0, 0, 0, 0, 1, 1, 0}};
    
    vector<vector<long long>> res = pow(e, d);

    cout << res[0][0] << '\n';
}