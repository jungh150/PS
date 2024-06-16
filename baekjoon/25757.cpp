#include <iostream>
#include <set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    set<string> p;

    int n;
    string game;
    cin >> n >> game;

    int mod;
    if (game == "Y") {
        mod = 1;
    } else if (game == "F") {
        mod = 2;
    } else if (game == "O") {
        mod = 3;
    }

    string str;
    for (int i = 0; i < n; i++) {
        cin >> str;
        p.insert(str);
    }

    int pn = p.size();
    cout << (pn / mod) << '\n';
}