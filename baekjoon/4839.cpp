#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

long long n;

void solve() {
    long long original = n;

    int num = 10000;
    vector<bool> p(10000, 1);
    p[0] = p[1] = 0;

    int sqnum = sqrt(num);
    for (int i = 2; i <= sqnum; i++) {
        if (!p[i]) continue;
        for (int j = i * i; j < num; j += i) p[j] = 0;
    }

    vector<int> prime; // 소수 배열
    long long tmp = 1;
    for (int i = 1; i < num; i++) {
        if (p[i]) {
            tmp *= i;
            if (tmp > n) {
                tmp /= i;
                break;
            }
            prime.push_back(i);
        }
    }

    int sz = prime.size();
    vector<int> ans(sz + 1);
    for (int i = sz; i > 0; i--) {
        ans[i] = n / tmp;
        n %= tmp;
        tmp /= prime[i - 1];
    }
    ans[0] = n;

    string s = "";
    vector<string> term;
    prime.push_back(0);
    for (int i = 0; i <= sz; i++) {
        if (i == 0) {
            if (ans[i] != 0) term.push_back(to_string(ans[i]));
            s += to_string(prime[i]);
        } else {
            if (ans[i] != 0) term.push_back(to_string(ans[i]) + "*" + s);
            s += "*";
            s += to_string(prime[i]);
        }
    }

    string ansstr;
    ansstr = term[0];
    for (int i = 1; i < term.size(); i++) {
        ansstr += " + ";
        ansstr += term[i];
    }

    cout << original << " = ";
    cout << ansstr << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    while (1) {
        cin >> n;
        if (n == 0) break;
        solve();
    }
}