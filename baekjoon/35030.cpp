#include <iostream>
#include <vector>
using namespace std;

vector<int> ps;
int MAX_VAL = 1e5;

void solve() {
    int n;
    cin >> n;
    cout << ps[n] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int num = 1e6;
    vector<bool> p(num, 1);
    p[0] = p[1] = 0;
    for (int i = 2; i * i <= num; i++) {
        if (p[i]) {
            for (int j = i * i; j < num; j += i) {
                p[j] = 0;
            }
        }
    }

    ps = vector<int>(MAX_VAL + 1, 0);
    for (int x = 1; x <= MAX_VAL; x++) {
        ps[x] = ps[x - 1];
        if (!p[x + 1]) continue;
        string s = to_string(x);
        int len = s.size();
        bool flag = true;
        for (int i = 1; i < len; i++) {
            if (!p[stoi(s.substr(0, i)) * stoi(s.substr(i, len - i)) + 1]) {
                flag = false;
                break;
            }
        }
        if (flag) ps[x]++;
    }

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}