#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string str;
int n;
string res;
bool fin = false;
vector<int> a;
vector<bool> chk;

void dfs(int idx) {
    if (fin) {
        return;
    }
    if (idx == n) {
        if (res > str) {
            for (char c: res) {
                cout << c;
            }
            cout << '\n';
            fin = true;
        }
        return;
    }
    for (int i = 0; i < n; i++) {
        if (!chk[i]) {
            chk[i] = true;
            res.replace(idx, 1, to_string(a[i]));
            dfs(idx + 1);
            if (fin) break;
            chk[i] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> str;
    res = str.substr();
    n = str.size();
    chk = vector<bool>(n);

    for (char c: str) {
        a.push_back(c - '0');
    }

    sort(a.begin(), a.end());

    dfs(0);
}
