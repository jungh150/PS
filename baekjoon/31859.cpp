#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    string s;
    cin >> n >> s;

    vector<bool> chk(26, 0);

    string tmp = "";
    int cnt = 0;
    for (char c: s) {
        if (!chk[c - 'a']) {
            tmp += c;
            chk[c - 'a'] = 1;
        } else {
            cnt++;
        }
    }

    tmp += to_string(cnt + 4);

    tmp = to_string(n + 1906) + tmp;

    reverse(tmp.begin(), tmp.end());

    tmp = "smupc_" + tmp;

    cout << tmp << '\n';
}