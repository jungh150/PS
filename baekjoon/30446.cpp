#include <iostream>
#include <vector>
#include <string>
using namespace std;

long long n;
int posn, endn;
long long ans = 0;
bool fin = false;
string res = "";

void dfs(int idx) {
    if (fin) return;
    if (idx == endn) {
        if (stoll(res) <= n) {
            ans++;
        } else {
            fin = true;
        }
        return;
    }
    if (idx == 0) {
        for (int i = 1; i < 10; i++) {
            res[idx] = res[posn - idx - 1] = i + '0';
            dfs(idx + 1);
            if (fin) return;
        }
    } else {
        for (int i = 0; i < 10; i++) {
            res[idx] = res[posn - idx - 1] = i + '0';
            dfs(idx + 1);
            if (fin) return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    posn = to_string(n).size();

    for (int i = 1; i < posn; i++) {
        long long tmp = 9;
        int endt = (i + 1) / 2;
        for (int j = 1; j < endt; j++) tmp *= 10;
        ans += tmp;
    }

    endn = (posn + 1) / 2;
    res.resize(posn, '0');

    dfs(0);

    cout << ans << '\n';
}