#include <iostream>
#include <vector>
using namespace std;

vector<int> fact;
vector<int> ans;
vector<int> mul;
vector<bool> chk;

int n, f;
bool fin = false;

void dfs(int idx, int res) {
    if (fin || res > f) {
        return;
    }
    if (idx == n) {
        if (res == f) {
            for (int x: ans) {
                cout << x << ' ';
            }
            cout << '\n';
            fin = true;
        }
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!chk[i]) {
            chk[i] = true;
            ans[idx] = i;
            dfs(idx + 1, res + mul[idx] * i);
            if (fin) break;
            chk[i] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> f;
    fact = vector<int>(n, 1);
    ans = vector<int>(n);
    mul = vector<int>(n);
    chk = vector<bool>(n + 1);

    int tmp = 1;
    for (int i = 1; i < n; i++) {
        tmp *= i;
        fact[i] = tmp;
    }

    for (int i = 0; i < n; i++) {
        mul[i] = fact[n - 1] / fact[i] / fact[n - 1 - i];
    }

    dfs(0, 0);
}