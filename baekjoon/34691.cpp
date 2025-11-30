#include <iostream>
using namespace std;

void solve() {
    while (1) {
        string s;
        cin >> s;

        if (s == "end") return;
        else if (s == "animal") cout << "Panthera tigris\n";
        else if (s == "tree") cout << "Pinus densiflora\n";
        else if (s == "flower") cout << "Forsythia koreana\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}