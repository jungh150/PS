#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<int> s(50);
    for (int i = 0; i < 50; i++) cin >> s[i];
    int mys;
    cin >> mys;

    int l = 0;
    int r = 50;
    while (l < r) {
        int m = (l + r) / 2;
        if (mys <= s[m]) l = m + 1;
        else r = m;
    }

    int myr = l;
    if (myr <= 5) cout << "A+\n";
    else if (myr <= 15) cout << "A0\n";
    else if (myr <= 30) cout << "B+\n";
    else if (myr <= 35) cout << "B0\n";
    else if (myr <= 45) cout << "C+\n";
    else if (myr <= 48) cout << "C0\n";
    else cout << "F\n";
}