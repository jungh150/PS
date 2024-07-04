#include <iostream>
#include <map>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    map<string, string> pwm;
    while (n--) {
        string addr, pw;
        cin >> addr >> pw;
        pwm.insert({addr, pw});
    }

    while (m--) {
        string taddr;
        cin >> taddr;
        cout << pwm[taddr] << '\n';
    }
}