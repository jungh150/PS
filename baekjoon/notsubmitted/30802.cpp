#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> ts(6);
    for (int i = 0; i < 6; i++) {
        cin >> ts[i];
    }
    
    int t, p;
    cin >> t >> p;

    int at = 0;
    int ap1, ap2;

    for (int i = 0; i < 6; i++) {
        at += ts[i] / t;
        if (ts[i] % t != 0) {
            at++;
        }
    }

    ap1 = n / p;
    ap2 = n % p;

    cout << at << '\n' << ap1 << ' ' << ap2 << '\n';
}